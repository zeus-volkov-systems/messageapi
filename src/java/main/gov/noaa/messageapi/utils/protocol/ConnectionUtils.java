package gov.noaa.messageapi.utils.protocol;

import java.util.ArrayList;
import java.util.Map;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.utils.general.ListUtils;

public class ConnectionUtils {

    public static CompletableFuture<IPacket> submitRecords(IConnection connection, IProtocolRecord record) {
        if (record != null) {
            return CompletableFuture.supplyAsync(() -> {
                return connection.process(record);
            });
        }
        return null;
    }

    /**
     * For a given list of named transformations, correlates each against a rawTransformationMap list,
     * adding it to the list if it exists, and then finding any referenced transformations, adding each
     * to the master list in turn. Combines all lists and returns a comprehensive list of unique transformation ids
     * that both a. exist, and b. are unique.
     * @param  namedTransformations  A list of transformations that are specified by id as being used by a given connection
     * @param  rawTransformationMaps A list of transformation maps that have available specifications from the container layer
     * @return                       A list of confirmed, comprehensive transformation ids that will be available to a connection
     */
    public static List<String> getConnectionTransformations(List<String> namedTransformations, List<Map<String,Object>> rawTransformationMaps) {
        List<String> connTransformations = new ArrayList<String>();
        return ListUtils.eliminateDuplicates(ListUtils.removeAllNulls(ListUtils.flatten(namedTransformations.stream().map(namedTransformation -> {
            return getFullConnectionList(namedTransformation, connTransformations, rawTransformationMaps);
        }).collect(Collectors.toList()))));
    }

    @SuppressWarnings("unchecked")
    public static List<String> getFullConnectionList(String candidate, List<String> confirmations, List<Map<String,Object>> sourceMaps) {
        Optional<Map<String,Object>> candidateMap = sourceMaps.stream().filter(sourceMap -> ((String) sourceMap.get("id")).equals(candidate)).findAny();
        if (candidateMap.isPresent()) {
            confirmations.add((String) candidateMap.get().get("id"));
            if (candidateMap.get().get("records") instanceof Map) {
                ((Map<String, Object>) candidateMap.get().get("records")).values().stream().map(candidateRecord -> {
                    if (candidateRecord instanceof Map) {
                        if (((Map<String,Object>)candidateRecord).containsKey("TRANSFORMATION")) {
                            return getFullConnectionList((String)((Map<String,Object>)candidateRecord).get("TRANSFORMATION"), confirmations, sourceMaps);
                        }
                    }
                    return confirmations;
                }).collect(Collectors.toList());
            }
        }
        return confirmations;
    }

}
