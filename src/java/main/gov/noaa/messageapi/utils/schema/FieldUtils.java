package gov.noaa.messageapi.utils.schema;

import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICompositeCondition;
import gov.noaa.messageapi.interfaces.IComparisonCondition;

import gov.noaa.messageapi.rejections.simple.SimpleRejection;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.schema.ConditionUtils;

/**
 * This static utility class holds generic and immutable methods related to
 * IField processing. Where possible, maps, filters, and other java8 parallelizable
 * mechanisms should be used. This class should only hold threadsafe methods.
 */
public class FieldUtils {

    /**
     * Updates each record in the request, removing any unset fields from the record.
     * Unset fields are not used by add operations.
     */
    public static void removeNonValuedFields(IRecord record) {
        record.setFields(record.getFields().stream()
        .filter(f -> f.getValue() != null).collect(Collectors.toList()));
    }

    /**
     * Returns a subset of the input fields list by filtering out those fields
     * without a set value.
     * @param  fields The input field set to filter
     * @return        A list of filtered fields containing only those with values.
     */
    public static List<IField> filterNonValuedFields(List<IField> fields) {
        return fields.stream().filter(f -> f.getValue() != null).collect(Collectors.toList());
    }

    /**
     * Checks a Field, evaluates required and available status.
     * Returns true if the field is available, or false otherwise.
     * @param  field The field to validate.
     * @return       a boolean indicating if the field is required and missing
     */
    public static boolean validateRequired(IField field) {
        if (field.isRequired() && field.getValue() == null) {
            return false;
        }
        return true;
    }

    /**
     * Validates each request record against required fields, ensuring that
     * each required field has data. All fields that are required but do not
     * have a value are assigned a rejection record and the total rejection record set
     * is updated.
     * @param rejections A rejection set to hold rejected request records
     */
    public static List<IRejection> validateRequired(IRequest request) {
        return request.getRecords().stream().map(r -> {
            IRejection rejection = new SimpleRejection(r);
            r.getFields().forEach(f -> {
                if (f.isRequired() && f.getValue() == null) {
                    rejection.addReason(String.format("Empty required field %s.", f.getName()));
                }
            });
            if (!rejection.getReasons().isEmpty()) {
                return rejection;
            } else {
                return null;
            }
        }).collect(Collectors.toList());
    }

    /**
     * Validates a list of conditions for the given record recursively. Composite
     * conditions are broken down into children with comparison conditions at the
     * terminus. The schema holds the operator factory to make the final comparison
     * conditions evaluations.
     * @param  schema     The schema holding the comparison operator factory.
     * @param  record     The record holding the fields to be compared
     * @param  conditions The conditions to evaluate
     * @return            Whether or not the record satisfies all conditions
     */
    public static boolean validateConditions(ISchema schema, IRecord record, List<ICondition> conditions) {
        if (conditions.size() > 0) {
            if (evaluateAndCondition(schema, record, conditions)) {
                return true;
            }
            return false;
        }
        return true;
    }

    /**
     * Uses the schema operator factory to validate a field against a given comparison condition.
     * @param  schema    The schema holding the comparison operators.
     * @param  type      The type of comparison to make (=, /=, >, <=, etc.) Any comparsion type is fine if specified in the operator factory.
     * @param  field     The field to be compared
     * @param  condition The condition to compare
     * @return           whether the field value matches the specified condition value
     */
    private static boolean validateFieldCondition(ISchema schema, String type, IField field, ICondition condition) {
        return schema.getOperator(type).compare(field, condition);
    }

    /**
     * Evaluates a record against a condition. Conditions in this method are either of
     * composite or comparison type. Composite conditions are broken down recursively
     * into comparison conditions and these conditions are then evaluated together (and or or).
     * @param  s         Schema holding the comparison operators
     * @param  r         The record holding the fields to be compared
     * @param  condition The condition for which to validate record fields
     * @return           whether the condition is satisfied
     */
    private static boolean evaluateFieldCondition(ISchema s, IRecord r, ICondition condition) {
        if (condition.getType().equals("comparison")) {
            IComparisonCondition c = (IComparisonCondition) condition;
            if (validateFieldCondition(s, r.getField(c.getField()).getType(), r.getField(c.getField()), c)) {
                return true;
            }
            return false;
        } else if (condition.getType().equals("composite")) {
            ICompositeCondition c = (ICompositeCondition) condition;
            if (condition.getOperator().equals("and")) {
                return evaluateAndCondition(s, r, ConditionUtils.getConditions(r, c.getConditions()));
            } else if (condition.getOperator().equals("or")) {
                return evaluateOrCondition(s, r, ConditionUtils.getConditions(r, c.getConditions()));
            }
            return false;
        }
        return false;
    }

    /**
     * Evaluates a record against an AND composite condition list. All conditions
     * in the list must recursively evaluate to true in order for this function to return true.
     * If any of the conditions evaluate to false, the entire condition evaluates to false.
     * Only the top level conditions are part of that evaluation (nested composite conditions
     * are evaluated on their own merits).
     * @param  s          Schema holding the comparison operators
     * @param  r          The record holding the fields to be compared
     * @param  conditions A list of conditions to evaluate
     * @return            whether or not the entire condition set is satisfied
     */
    private static boolean evaluateAndCondition(ISchema s, IRecord r, List<ICondition> conditions) {
        List<Boolean> results = conditions.stream()
            .map(c -> {
                return evaluateFieldCondition(s, r, c);
            }).collect(Collectors.toList());
        if (ListUtils.eliminateDuplicates(results).contains(true) && results.size() == 1) {
            return true;
        }
        return false;
    }

    /**
     * Evaluates a record against an OR composite condition list. At least one
     * of the conditions in the list must recursively evaluate to true for this
     * function to return true. Only the top level conditions are part of that
     * evaluation (nested composite conditions are evaluated on their own merits).
     * @param  s          Schema holding the comparison operators
     * @param  r          The record holding the fields to be compared
     * @param  conditions A list of conditions to evaluate
     * @return            whether or not the entire condition set is satisfied
     */
    private static boolean evaluateOrCondition(ISchema s, IRecord r, List<ICondition> conditions) {
        List<Boolean> results = conditions.stream()
            .map(c -> evaluateFieldCondition(s, r, c)).collect(Collectors.toList());
        if (ListUtils.eliminateDuplicates(results).contains(true)) {
            return true;
        }
        return false;
    }
}
