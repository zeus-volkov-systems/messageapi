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
     * [getConnectionTransformations description]
     * @param  namedTransformations  [description]
     * @param  rawTransformationMaps [description]
     * @return                       [description]
     */
    public static List<String> getConnectionTransformations(List<String> namedTransformations, List<Map<String,Object>> rawTransformationMaps) {
        List<String> connTransformations = new ArrayList<String>();
        return ListUtils.removeAllNulls(ListUtils.flatten(namedTransformations.stream().map(namedTransformation -> {
            return getFullConnectionList(namedTransformation, connTransformations, rawTransformationMaps);
        }).collect(Collectors.toList())));
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
