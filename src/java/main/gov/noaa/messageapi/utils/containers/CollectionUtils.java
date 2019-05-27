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
    public static List<ICollection> buildCollections(List<Map<String,Object>> collectionMaps) {
        return collectionMaps.stream().map(m -> {
            return new DefaultCollection(m);
        }).collect(Collectors.toList());
    }

    /**
     * Updates container record field set values with any schema field values with a matching field.
     * @param  containerRecord The container record containing field sets with empty fields
     * @param  schemaFields    A flat set of fields that need to be collectionned
     * @return                 The updated container record with all values set
     */
    public static IContainerRecord setFieldValues(IContainerRecord containerRecord, List<IField> schemaFields) {
        schemaFields.stream().forEach(schemaField -> {
            containerRecord.getCollections().stream().forEach(collection -> {
                collection.getFields().stream().forEach(collectionField -> {
                    if (schemaField.getName().equals(collectionField.getName())) {
                        collectionField.setValue(schemaField.getValue());
                    }
                });
            });
        });
        return containerRecord;
    }

    public static IContainerRecord validateCollectionConditions(ISchema schema, IContainerRecord containerRecord, IRecord requestRecord) {
        List<ICollection> validCollections = containerRecord.getCollections().stream().map(collection -> {
            List<String> conditionIds = collection.getConditionIds();
            IRecord collectionRecord = new SchemaRecord(collection.getFields());
            Map<String, List<String>> conditionMap = ConditionUtils.getChildConditionMap(requestRecord);
            List<String> collectionConditionIds = new ArrayList<String>();
            conditionMap.entrySet().stream().forEach(conditionEntry -> {
                if (conditionIds.contains(conditionEntry.getKey())) {
                    collectionConditionIds.add(conditionEntry.getKey());
                    collectionConditionIds.addAll(conditionEntry.getValue());
                }
            });
            collectionRecord.setConditions(requestRecord.getConditions().stream()
                                        .filter(rCond -> collectionConditionIds.contains(rCond.getId()))
                                        .collect(Collectors.toList()));
            if (!FieldUtils.validateConditions(schema, collectionRecord, ConditionUtils.getTopLevelConditions(collectionRecord))) {
                return null;
            } else {
                return collection;
            }
        }).collect(Collectors.toList());
        IContainerRecord validatedRecord = new ContainerRecord(ListUtils.removeAllNulls(validCollections));
        return validatedRecord;
    }


}
