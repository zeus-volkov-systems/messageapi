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

    public static IContainerRecord setFieldValues(IContainerRecord containerRecord, List<IField> fields) {
        return containerRecord;
    }


}
