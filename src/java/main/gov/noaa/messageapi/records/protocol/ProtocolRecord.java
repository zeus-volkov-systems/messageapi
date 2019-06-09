package gov.noaa.messageapi.records.protocol;

import java.util.Map;
import java.util.List;
import java.util.UUID;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.protocol.ProtocolRecordUtils;


/**
 * A protocol record is the primary communication center
 * of the protocol layer. Endpoint connections use these records
 *  (one record per connection) to manage record access via
 *  asking for specific named collections, classifiers, or transformations
 *  that are available to it. These are all named in the specification.
 *  @author Ryan Berkheimer
 */
public class ProtocolRecord implements IProtocolRecord {

    private Map<String, Map<String,Object>> transformationMap;
    private Map<IRecord,Map<String,Object>> recordMap;
    private List<UUID> uuids;
    private String connectionId;

    public ProtocolRecord(IConnection connection, Map<IRecord, Map<String,Object>> recordMap) {
        this.setConnectionId(connection.getId());
        this.setTransformationMap(connection.getTransformationMap());
        this.setRecordMap(recordMap);
        this.setUUIDs(recordMap);
    }

    public String getConnectionId() {
        return this.connectionId;
    }

    public Map<String, Map<String,Object>> getTransformationMap(){
        return this.transformationMap;
    }

    public List<IRecord> getRecords() {
        return new ArrayList<IRecord>(this.recordMap.keySet());
    }

    public List<UUID> getUUIDs() {
        return this.uuids;
    }

    public Map<IRecord,Map<String,Object>> getRecordMap() {
        return this.recordMap;
    }

    public List<IRecord> getRecordsByCollection(String collectionId) {
        List<IRecord> collectionRecords = this.recordMap.entrySet().stream().filter(e -> {
            if (((String)e.getValue().get("COLLECTION")).equals(collectionId)) {
                return true;
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
        if (collectionRecords != null && collectionRecords.size() > 0) {
            return collectionRecords.stream().map(r -> r.getCopy()).collect(Collectors.toList());
        }
        return new ArrayList<IRecord>();
    }

    public List<IRecord> getRecordsByUUID(UUID uuid) {
        List<IRecord> uuidRecords = this.recordMap.entrySet().stream().filter(e -> {
            if (((UUID)e.getValue().get("UUID")).equals(uuid)) {
                return true;
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
        if (uuidRecords != null && uuidRecords.size() > 0) {
            return uuidRecords.stream().map(r -> r.getCopy()).collect(Collectors.toList());
        }
        return new ArrayList<IRecord>();
    }

    @SuppressWarnings("unchecked")
    public List<IRecord> getRecordsByClassifier(String key, Object value) {
        List<IRecord> classRecords = this.recordMap.entrySet().stream().filter(e -> {
            if (((Map<String,Object>)e.getValue().get("CLASSIFIERS")).keySet().contains(key)) {
                if (((List<String>)((Map<String,Object>)e.getValue().get("CLASSIFIERS")).get(key)).contains(value)) {
                    return true;
                }
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
        if (classRecords != null && classRecords.size() > 0) {
            return classRecords.stream().map(r -> r.getCopy()).collect(Collectors.toList());
        }
        return new ArrayList<IRecord>();
    }

    @SuppressWarnings("unchecked")
    public List<IRecord> getRecordsByTransformation(String transformationId) {
        if (this.getTransformationMap().containsKey(transformationId)) {
            ITransformation transformationInstance = (ITransformation)this.getTransformationMap().get(transformationId).get("instance");
            Map<String,String> parameterMapSpec = (Map<String,String>)this.getTransformationMap().get(transformationId).get("parameters");
            String uuidParam = ProtocolRecordUtils.getUUIDParameter(parameterMapSpec);
            Map<String,List<IRecord>> parameterMap = ProtocolRecordUtils.buildParameterMap(this, parameterMapSpec);
            if (uuidParam != null && !uuidParam.isEmpty()) {
                return ListUtils.flatten(this.getUUIDs().stream().map(uuid -> {
                    Map<String,List<IRecord>> uuidParams = new HashMap<String,List<IRecord>>(parameterMap);
                    uuidParams.replace(uuidParam, this.getRecordsByUUID(uuid));
                    return transformationInstance.process(uuidParams);
                }).collect(Collectors.toList()));
            } else {
                return transformationInstance.process(parameterMap);
            }
        }
        return null;
    }

    private void setTransformationMap(Map<String, Map<String,Object>> transformationMap) {
        this.transformationMap = transformationMap;
    }

    private void setConnectionId(String connectionId) {
        this.connectionId = connectionId;
    }

    private void setRecordMap(Map<IRecord, Map<String,Object>> recordMap) {
        this.recordMap = recordMap;
    }

    private void setUUIDs(Map<IRecord, Map<String,Object>> recordMap) {
        this.uuids = ListUtils.eliminateDuplicates(recordMap.values().stream().map(v -> {
            return (UUID) v.get("UUID");
        }).collect(Collectors.toList()));
    }

}
