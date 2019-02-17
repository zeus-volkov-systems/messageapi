package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IBin;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.bins.DefaultBin;

public class BinUtils {

    public static List<IBin> buildBins(List<Map<String,Object>> binMaps) {
        return binMaps.stream().map(m -> {
            return new DefaultBin(m);
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
            containerRecord.getBins().stream().forEach(bin -> {
                bin.getFields().stream().forEach(binField -> {
                    if (schemaField.getName().equals(binField.getName())) {
                        binField.setValue(schemaField.getValue());
                    }
                });
            });
        });
        return containerRecord;
    }


}
