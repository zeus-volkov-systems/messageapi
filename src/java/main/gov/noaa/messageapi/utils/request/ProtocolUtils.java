package gov.noaa.messageapi.utils.request;

import java.util.HashMap;
import java.util.UUID;
import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IBin;
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
        List<String> connBins = connection.getBins();
        Map<String,List<String>> connClassifiers = connection.getClassifiers();
        List<Map<IRecord, Map<String,Object>>> recordList = ListUtils.flatten(containerRecords.stream().map(containerRecord -> {
            UUID recordId = containerRecord.getId();
            return ListUtils.removeAllNulls(containerRecord.getBins().stream().map(bin -> {
                return convertBinToRecord(bin, recordId, connBins, connClassifiers);
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList()));
        return new ProtocolRecord(connId, MapUtils.mergeMapList(recordList));
    }

    public static Map<IRecord, Map<String,Object>> convertBinToRecord(IBin bin, UUID recordId,
                                                        List<String> connBins, Map<String,List<String>> connClassifiers) {
        String binId = bin.getId();
        Map<String, Object> binClassifiers = bin.getClassifiers();
        if (binMatch(binId, connBins) || classifierMatch(binClassifiers, connClassifiers)) {
            return makeBinRecordMap(recordId, new SchemaRecord(bin.getFields()), binId, binClassifiers);
        }
        return null;
    }

    public static Map<IRecord,Map<String,Object>> makeBinRecordMap(UUID id, IRecord record, String binId, Map<String,Object> classifiers) {
        Map<IRecord,Map<String,Object>> retMap = new HashMap<IRecord, Map<String,Object>>();
        Map<String, Object> valMap = new HashMap<String, Object>();
        valMap.put("CLASSIFIERS",classifiers);
        valMap.put("BIN", binId);
        valMap.put("UUID", id);
        retMap.put(record, valMap);
        return retMap;
    }

    public static Boolean binMatch(String binId, List<String> connBins) {
        if (connBins.contains(binId)) {
            return true;
        }
        return false;
    }

    public static Boolean classifierMatch(Map<String,Object> binClassifiers,
                                          Map<String,List<String>> connClassifiers) {
        List<String> matchKeys = ListUtils.removeAllNulls(binClassifiers.keySet()
                                                                        .stream()
                                                                        .filter(key -> connClassifiers
                                                                                       .keySet()
                                                                                       .contains(key))
                                                                        .collect(Collectors.toList()));
        if (classifierValueMatch(matchKeys, binClassifiers, connClassifiers)) {
            return true;
        }
        return false;
    }

    @SuppressWarnings("unchecked")
    public static Boolean classifierValueMatch(List<String> keys,
                                                Map<String,Object> binClassifiers,
                                                Map<String,List<String>> connClassifiers) {
        List<String> fullMatch = ListUtils.removeAllNulls(keys
                                                          .stream()
                                                          .filter(key -> {
            Object classVal = binClassifiers.get(key);
            if (classVal instanceof List) {
                if (((List<Object>) classVal).stream().filter(val -> connClassifiers
                                                                     .get(key)
                                                                     .contains(val))
                                                                     .findAny()
                                                                     .isPresent()) {
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
