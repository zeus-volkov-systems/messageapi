package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ISchema;

import gov.noaa.messageapi.records.schema.SchemaRecord;
import gov.noaa.messageapi.records.container.ContainerRecord;
import gov.noaa.messageapi.collections.DefaultCollection;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.schema.ConditionUtils;
import gov.noaa.messageapi.utils.schema.FieldUtils;

/**
 * This class contains static utilities for building, validating, and otherwise
 * working with collection containers and collection components including fields
 * and conditions. 
 * @author Ryan Berkheimer
 */
public class CollectionUtils {

    /**
     * Uses a list of maps containing collection specifications to create a list
     * of default collection objects. This involves converting every map into a
     * unique Collection object based on the DefaultCollection class, using
     * the properties outlined in the map as specification.
     * @param  collectionMaps A list of collection maps containing instantiation information
     * @return                A list of DefaultCollection objects
     */
    public static List<ICollection> buildCollections(final List<Map<String, Object>> collectionMaps) {
        return collectionMaps.stream().map(m -> {
            return new DefaultCollection(m);
        }).collect(Collectors.toList());
    }

    /**
     * Updates container record field set values with any schema field values with a
     * matching field.
     * 
     * @param containerRecord The container record containing field sets with empty
     *                        fields
     * @param schemaFields    A flat set of fields that need to be collectionned
     * @return The updated container record with all values set
     */
    public static IContainerRecord setFieldValues(final IContainerRecord containerRecord,
            final List<IField> schemaFields) {
        schemaFields.stream().forEach(schemaField -> {
            containerRecord.getCollections().stream().forEach(collection -> {
                collection.getFields().stream().forEach(collectionField -> {
                    if (schemaField.getName().equals(collectionField.getName())) {
                        collectionField.setValue(schemaField.getValue());
                        collectionField.setType(schemaField.getType());
                        collectionField.setValid(schemaField.isValid());
                    }
                });
            });
        });
        return containerRecord;
    }

    /**
     * Looks at all of the collections in a container record, validating each
     * collection against any conditions that were specified on a request-wide
     * basis. The conditions used for collection validation are held in a request
     * record - these conditions are applied to all collections, by first reducing
     * the set of conditions on a per-collection basis (looking for only
     * valued-conditions), then making sure that the collection satisfies the
     * conditions. If the collection does satisfy the conditions, it is kept - if
     * not, it is discarded. All kept conditions are then used to create a new
     * ContainerRecord, and this new ContainerRecord is returned.
     * 
     * @param schema          The existing session schema holding the condition
     *                        factory
     * @param containerRecord A container record holding collections to be validated
     * @param requestRecord   The request record holding valued conditions
     * @return Returns a new ContainerRecord that contains only validated
     *         collections
     */
    public static IContainerRecord validateCollectionConditions(final ISchema schema,
            final IContainerRecord containerRecord, final IRecord requestRecord) {
        final List<ICollection> validCollections = containerRecord.getCollections().stream().map(collection -> {
            final List<String> conditionIds = collection.getConditionIds();
            final IRecord collectionRecord = new SchemaRecord(collection.getFields());
            final Map<String, List<String>> conditionMap = ConditionUtils.getChildConditionMap(requestRecord);
            final List<String> collectionConditionIds = new ArrayList<String>();
            conditionMap.entrySet().stream().forEach(conditionEntry -> {
                if (conditionIds.contains(conditionEntry.getKey())) {
                    collectionConditionIds.add(conditionEntry.getKey());
                    collectionConditionIds.addAll(conditionEntry.getValue());
                }
            });
            collectionRecord.setConditions(requestRecord.getConditions().stream()
                    .filter(rCond -> collectionConditionIds.contains(rCond.getId())).collect(Collectors.toList()));
            if (!FieldUtils.validateConditions(schema, collectionRecord,
                    ConditionUtils.getTopLevelConditions(collectionRecord))) {
                return null;
            } else {
                return collection;
            }
        }).collect(Collectors.toList());
        final IContainerRecord validatedRecord = new ContainerRecord(ListUtils.removeAllNulls(validCollections),
                containerRecord.getTransformations());
        return validatedRecord;
    }


}
