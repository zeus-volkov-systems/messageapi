package gov.noaa.messageapi.utils.request;

import java.util.HashMap;
import java.util.UUID;
import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.utils.general.MapUtils;
import gov.noaa.messageapi.utils.general.ListUtils;

import gov.noaa.messageapi.records.schema.SchemaRecord;
import gov.noaa.messageapi.records.protocol.ProtocolRecord;

public class ProtocolUtils {

    public static List<IProtocolRecord> convertContainerRecords(IProtocol protocol, List<IContainerRecord> containerRecords) {
        return protocol.getConnections().stream().map(c -> {
            return createProtocolRecord(c, containerRecords);
        }).collect(Collectors.toList());
    }

    public static IProtocolRecord createProtocolRecord(IConnection connection, List<IContainerRecord> containerRecords) {
        String connId = connection.getId();
        List<String> connCollections = connection.getCollections();
        Map<String,List<Object>> connClassifiers = connection.getClassifiers();
        List<Map<IRecord, Map<String,Object>>> recordList = ListUtils.flatten(containerRecords.stream().map(containerRecord -> {
            UUID recordId = containerRecord.getId();
            return ListUtils.removeAllNulls(containerRecord.getCollections().stream().map(collection -> {
                return convertCollectionToRecord(collection, recordId, connCollections, connClassifiers);
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList()));
        return new ProtocolRecord(connId, MapUtils.mergeMapList(recordList));
    }

    public static Map<IRecord, Map<String,Object>> convertCollectionToRecord(ICollection collection, UUID recordId,
                                                        List<String> connCollections, Map<String,List<Object>> connClassifiers) {
        String collectionId = collection.getId();
        Map<String, Object> collectionClassifiers = collection.getClassifiers();
        if (collectionMatch(collectionId, connCollections) || classifierMatch(collectionClassifiers, connClassifiers)) {
            return makeCollectionRecordMap(recordId, new SchemaRecord(collection.getFields()), collectionId, collectionClassifiers);
        }
        return null;
    }

    public static Map<IRecord,Map<String,Object>> makeCollectionRecordMap(UUID id, IRecord record, String collectionId, Map<String,Object> classifiers) {
        Map<IRecord,Map<String,Object>> retMap = new HashMap<IRecord, Map<String,Object>>();
        Map<String, Object> valMap = new HashMap<String, Object>();
        valMap.put("UUID", id);
        valMap.put("COLLECTION", collectionId);
        valMap.put("CLASSIFIERS",classifiers);
        retMap.put(record, valMap);
        return retMap;
    }

    public static Boolean collectionMatch(String collectionId, List<String> connCollections) {
        if (connCollections.contains(collectionId) || connCollections.contains("*")) {
            return true;
        }
        return false;
    }

    public static Boolean classifierMatch(Map<String,Object> collectionClassifiers, Map<String,List<Object>> connClassifiers) {
        List<String> matchKeys = ListUtils.removeAllNulls(collectionClassifiers.keySet().stream().filter(key -> connClassifiers.keySet().contains(key)).collect(Collectors.toList()));
        if (classifierValueMatch(matchKeys, collectionClassifiers, connClassifiers)) {
            return true;
        }
        return false;
    }

    @SuppressWarnings("unchecked")
    public static Boolean classifierValueMatch(List<String> keys, Map<String,Object> collectionClassifiers, Map<String,List<Object>> connClassifiers) {
        List<String> fullMatch = ListUtils.removeAllNulls(keys.stream().filter(key -> {
            Object classVal = collectionClassifiers.get(key);
            if (classVal instanceof List) {
                if (((List<Object>) classVal).stream().filter(val -> connClassifiers.get(key).contains(val)).findAny().isPresent()) {
                    return true;
                }
                return false;
            } else {
                if (connClassifiers.get(key).contains(classVal)) {
                    return true;
                }
                return false;
            }
        }).collect(Collectors.toList()));
        if (!ListUtils.isNullOrEmpty(fullMatch)) {
            return true;
        }
        return false;
    }

}
