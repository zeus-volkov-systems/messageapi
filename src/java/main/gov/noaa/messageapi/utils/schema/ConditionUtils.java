package gov.noaa.messageapi.utils.schema;

import java.util.Set;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IComparisonCondition;
import gov.noaa.messageapi.utils.general.ListUtils;


/**
 * ConditionUtils is a static utility class holding methods related to condition
 * preparation and processing. Methods in this class typically operate on
 * IRecords or IConditions.
 * @author Ryan Berkheimer
 */
public class ConditionUtils {


    /**
     * Used to nullify comparison conditions on the passed record. Any values that are already
     * in place on a condition contained in the passed record will be set to null
     * (if the condition is a comparison condition)
     * The same record will be returned.
     * @param  record A record containing conditions to be nullified
     * @return        The same record that is passed in, with its conditions all holding null as values
     */
    public static IRecord nullifyComparisonConditions(IRecord record) {
        record.getConditions().stream().forEach(c -> {
            if (c.getType().equals("comparison")) {
                c.setValue(null);
            }
        });
        return record;
    }

    /**
     * Returns a list of conditions matching the condition ids for a given record.
     * @param  record       The record holding the desired conditions
     * @param  conditionIds A list of condition ids to retrieve conditions for
     * @return              A list of IConditions matching conditionIds attached to the specified record
     */
    public static List<ICondition> getConditions(IRecord record, List<String> conditionIds) {
        return conditionIds.stream().map(id -> record.getCondition(id)).collect(Collectors.toList());
    }

    /**
     * Returns a subset of the input conditions list by filtering out those conditions
     * without a set value.
     * @param  conditions The input field set to filter
     * @return        A list of filtered fields containing only those with values.
     */
    public static List<ICondition> filterNonValuedConditions(List<ICondition> conditions) {
        return conditions.stream().filter(c -> c.getValue() != null).collect(Collectors.toList());
    }

    /**
     * For a given record, filters all conditions corresponding to a field that is no longer
     * attached to a record. This is done by first assembling a current map of condtitionIds to
     * comparison Condition ids, and then filtering out conditionIDs for which referenced
     * comparison Ids correspond to a field that is not attached to the record.
     * @param r The record holding the conditions to filter
     */
    public static List<ICondition> filterFieldlessConditions(IRecord r) {
        Map<String, List<String>> conditionMap = getRootConditionMap(r);
        Set<String> valuedConditions = conditionMap.entrySet().stream().filter(e -> {
            if (validateConditionFields(e.getValue(), r)) {
                return true;
            } else {
                return false;
            }
        }).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue)).keySet();
        return r.getConditions().stream().filter(c -> valuedConditions.contains(c.getId())).collect(Collectors.toList());
    }


    /**
     * For a given record, removes all conditions corresponding to a field that is no longer
     * attached to a record. This is done by first assembling a current map of condtitionIds to
     * comparison Condition ids, and then filtering out conditionIDs for which referenced
     * comparison Ids correspond to a field that is not attached to the record.
     * @param r The record to be updated
     */
    public static void removeFieldlessConditions(IRecord r) {
        Map<String, List<String>> conditionMap = getRootConditionMap(r);
        Set<String> valuedConditions = conditionMap.entrySet().stream().filter(e -> {
            if (validateConditionFields(e.getValue(), r)) {
                return true;
            } else {
                return false;
            }
        }).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue)).keySet();
        r.setConditions(r.getConditions().stream()
            .filter(c -> valuedConditions.contains(c.getId())).collect(Collectors.toList()));
    }

    /**
     * Updates the conditions on a record, removing those which directly
     * or indirectly reference a comparison condition which holds no assigned
     * value.
     * @param r The record holding the conditions which will be updated
     */
    public static void removeNonValuedConditions(IRecord r) {
        Map<String, List<String>> conditionMap = getRootConditionMap(r);
        Set<String> valuedConditions = conditionMap.entrySet().stream().filter(e -> {
            if (validateConditionValues(e.getValue(), r)) {
                return true;
            } else {
                return false;
            }
        }).collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue)).keySet();
        r.setConditions(r.getConditions().stream()
        .filter(c -> valuedConditions.contains(c.getId())).collect(Collectors.toList()));
    }

    /**
     * Compares a list of comparison condition fields corresponding to a record condition
     * with all fields currently attached to the record. If all fields are accounted for,
     * the condition is accepted. If a condition references a field that isn't attached,
     * that condition is invalidated.
     * @param  conditionIds A list of condition ids corresponding to a record condition.
     * @param  record       A record that will be updated according to fields and conditions
     * @return              true if a condition does not reference missing fields, false if it does
     */
    public static boolean validateConditionFields(List<String> conditionIds, IRecord record) {
        List<String> conditionFields = conditionIds.stream()
        .map(cid -> {
            IComparisonCondition condition = (IComparisonCondition) record.getCondition(cid);
            return condition.getField();
        }).collect(Collectors.toList());
        List<String> fieldNames = record.getFields().stream()
        .map(f -> f.getName()).collect(Collectors.toList());
        if (fieldNames.containsAll(conditionFields)) {
            return true;
            }
        return false;
    }

    /**
     * Invalidates any record conditions which are not valued (i.e., if they were never given a value)
     * @param  conditionIds A list of condition ids corresponding to comparison conditions linked to the condition.
     * @param  record       The record to which the conditions belong
     * @return              true if a condition is completely valued, false if otherwise
     */
    public static boolean validateConditionValues(List<String> conditionIds, IRecord record) {
        for (String conditionId: conditionIds) {
            if (record.getCondition(conditionId).getValue() == null) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns a list of conditions which are considered 'record primary', or
     * 'top level conditions'. This means that the conditions returned by this
     * method are not referenced by any other condition.
     * @param  conditionMap A map containing conditionIds (keys) and associated child conditionIds (values)
     * @param  r            The record containing the conditions described by the conditionMap
     * @return              A list of primary record conditions.
     */
    public static List<ICondition> getTopLevelConditions(IRecord r) {
        Map<String, List<String>> conditionMap = getChildConditionMap(r);
        Set<String> keys = conditionMap.keySet();
        List<String> values = ListUtils.flatten(conditionMap.values());
        List<String> topLevelKeys = keys.stream().filter(k -> !values.contains(k)).collect(Collectors.toList());
        return topLevelKeys.stream().map(tk -> r.getCondition(tk)).collect(Collectors.toList());
    }

    /**
     * Returns a map containing condition ids corresponding to all comparison condition ids
     * that they reference. This map will hold a key set of every condition attached to the
     * record, where each key holds a list value containing any comparison conditions that it
     * contains. In this map, comparison condition keys will hold themselves in their values.
     * @param  r  A record containing the conditions to process
     * @return   A map containing all current record conditions (id key with root comparison condition list value)
     */
    private static Map<String, List<String>> getRootConditionMap(IRecord r) {
        return r.getConditions().stream()
        .collect(Collectors.toMap(c -> c.getId(),
        c -> getRootConditions(new ArrayList<String>(), c, r)));
    }

    /**
     * Returns a map containing condition ids corresponding to all condition ids
     * that they reference as children. The produced map will hold a key set of
     * every condition attached to the record, where each key holds a list value
     * containing ONLY children CONTAINED by that value. I.E, values for comparison
     * conditions will be empty.
     * @param  r  A record containing the conditions to process
     * @return   A map containing all current record conditions.
     */
    private static Map<String, List<String>> getChildConditionMap(IRecord r) {
        return r.getConditions().stream()
            .collect(Collectors.toMap(c -> c.getId(),
            c -> filterChildConditionMap(getChildConditions(new ArrayList<String>(), c, r),c)));
    }

    /**
     * Removes a condition id from a list of condition ids if that condition
     * is a comparison condition and the list contains that comparison condition
     * id.
     * @param  children A list of condition ids
     * @param  c        A condition to evaluate
     * @return          A list containing the updated children conditions
     */
    private static List<String> filterChildConditionMap(List<String> children, ICondition c) {
        return children.stream().filter(child -> {
            if (child.equals(c.getId())) {
                return false;
            }
            return true;
        }).collect(Collectors.toList());
    }

    @SuppressWarnings("unchecked")
    /**
     * Recursive method that assembles a list of root comparison conditions for
     * a given condition. For example, if we pass a composite condition that references
     * other composite conditions that eventually references a set of comparison conditions,
     * this method will return a list of strings containing every comparison condition at the
     * root of the composite conditions. If a comparison condition is passed, the list will
     * contain the comparison condition id.
     * @param  list A list to hold condition ids
     * @param  c    The condition to process
     * @param  r    The condition's parent record
     * @return      The completed (filled out) list
     */
    private static List<String> getRootConditions(List<String> list, ICondition c, IRecord r) {
        if (c.getType().equals("comparison")) {
            list.add(c.getId());
        } else if (c.getType().equals("composite")) {
            List<String> compositeConditions = (List<String>) c.getValue();
            compositeConditions.stream()
            .map(composite -> {
                return getRootConditions(list, r.getCondition(composite), r);
            }).collect(Collectors.toList());
        }
        return ListUtils.eliminateDuplicates(list);
    }

    @SuppressWarnings("unchecked")
    /**
     * Recursive method that update a mutable list of the id of all children conditions
     * that are part of the given condition.
     * @param  list The list that is being maintained containing contained conditions
     * @param  c    The condition to process
     * @param  r    The record containing the condition
     * @return      the list without duplicates
     */
    private static List<String> getChildConditions(List<String> list, ICondition c, IRecord r) {
        if (c.getType().equals("comparison")) {
            list.add(c.getId());
        } else if (c.getType().equals("composite")) {
            List<String> compositeConditions = (List<String>) c.getValue();
            compositeConditions.stream()
            .map(composite -> {
                list.add(composite);
                return getChildConditions(list, r.getCondition(composite), r);
            }).collect(Collectors.toList());
        }
        return ListUtils.eliminateDuplicates(list);
    }

}
