package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IFieldSet;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.fieldsets.FieldSet;

public class FieldSetUtils {

    public static List<IFieldSet> buildFieldSets(List<Map<String,Object>> fieldContainerMaps) {
        return fieldContainerMaps.stream().map(m -> {
            return new FieldSet(m);
        }).collect(Collectors.toList());
    }

    /**
     * Updates container record field set values with any schema field values with a matching field.
     * @param  containerRecord The container record containing field sets with empty fields
     * @param  schemaFields    A flat set of fields that need to be binned
     * @return                 The updated container record with all values set
     */
    public static IContainerRecord setFieldValues(IContainerRecord containerRecord, List<IField> schemaFields) {
        schemaFields.stream().forEach(schemaField -> {
            containerRecord.getFieldSets().stream().forEach(fieldSet -> {
                fieldSet.getFields().stream().forEach(fieldSetField -> {
                    if (schemaField.getName().equals(fieldSetField.getName())) {
                        fieldSetField.setValue(schemaField.getValue());
                    }
                });
            });
        });
        return containerRecord;
    }


}
