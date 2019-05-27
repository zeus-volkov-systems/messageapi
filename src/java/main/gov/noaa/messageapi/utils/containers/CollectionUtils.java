package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.collections.DefaultCollection;


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


}
