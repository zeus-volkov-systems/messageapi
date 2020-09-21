package gov.noaa.messageapi.utils.protocol;

import java.util.HashMap;
import java.util.stream.Collectors;
import java.util.AbstractMap;
import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import java.util.List;
import java.util.Map;


/**
 * This class contains static utilities for parsing, creating, or otherwise manipulating
 * internal protocol record components.
 * @author Ryan Berkheimer
 */
public class ProtocolRecordUtils {

    /**
     * Checks a parameter map by counting the results of a filtering operation,
     * where the parameter has to be for UUIDs. UUID keys are important for
     * transformations, because if there is a UUID key, the encapsulating transformation
     * is applied to every UUID found in the protocol record map.
     * @param  parameterMap A parameter map containing keys/values of transformation map collections
     * @return              True if there's a UUID key, false otherwise.
     */
    public static String getUUIDParameter(final Map<String, String> parameterMap) {
        final List<String> uuidStrings = ListUtils.removeAllNulls(parameterMap.entrySet().stream().map(e -> {
            if (e.getValue().equals("UUID")) {
                return e.getKey();
            }
            return null;
        }).collect(Collectors.toList()));
        if (uuidStrings.size() == 1) {
            return uuidStrings.get(0);
        }
        return null;
    }

    public static Map<String, List<IRecord>> buildParameterMap(final IProtocolRecord protocolRecord,
            final Map<String, String> parameterMapSpec) {
        final List<Map.Entry<String, List<IRecord>>> entries = ProtocolRecordUtils.buildParameterEntries(protocolRecord,
                parameterMapSpec);
        final Map<String, List<IRecord>> parameterMap = new HashMap<String, List<IRecord>>();
        entries.stream().forEach(e -> {
            parameterMap.put(e.getKey(), e.getValue());
        });
        return parameterMap;
    }

    public static List<Map.Entry<String, List<IRecord>>> buildParameterEntries(final IProtocolRecord protocolRecord,
            final Map<String, String> parameterMapSpec) {
        return ListUtils.removeAllNulls(parameterMapSpec.entrySet().stream().map(e -> {
            final String[] parameterValueArray = e.getValue().split("=");
            switch(parameterValueArray[0]) {
                case "CLASSIFIER":
                    return new AbstractMap.SimpleEntry<String,List<IRecord>>(e.getKey(),
                                protocolRecord.getRecordsByClassifier(parameterValueArray[1], parameterValueArray[2]));
                case "COLLECTION":
                    return new AbstractMap.SimpleEntry<String,List<IRecord>>(e.getKey(),
                                protocolRecord.getRecordsByCollection(parameterValueArray[1]));
                case "TRANSFORMATION":
                    return new AbstractMap.SimpleEntry<String,List<IRecord>>(e.getKey(),
                                protocolRecord.getRecordsByTransformation(parameterValueArray[1]));
                case "UUID":
                    return new AbstractMap.SimpleEntry<String,List<IRecord>>(e.getKey(), null);
            }
            return null;
        }).collect(Collectors.toList()));
    }


}
