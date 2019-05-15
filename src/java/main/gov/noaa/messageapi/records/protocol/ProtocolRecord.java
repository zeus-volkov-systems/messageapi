package gov.noaa.messageapi.records.protocol;

import java.util.UUID;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IConnection;


/**
 * A protocol record is the primary communication center
 * of the protocol layer. Endpoint connections use these records
 *  (one record per connection) to manage record access via
 *  asking for specific named collections, classifiers, or transformations
 *  that are available to it. These are all named in the specification.
 */
public class ProtocolRecord implements IProtocolRecord {

    private IConnection connection;
    private Map<IRecord,Map<String,Object>> recordMap;

    public ProtocolRecord(IConnection connection, Map<IRecord, Map<String,Object>> recordMap) {
        this.setConnection(connection);
        this.setRecords(recordMap);
    }

    public IConnection getConnection(){
        return this.connection;
    }

    public List<IRecord> getRecords() {
        return new ArrayList<IRecord>(this.recordMap.keySet());
    }

    public List<IRecord> getRecordsByCollection(String collectionId) {
        return this.recordMap.entrySet().stream().filter(e -> {
            if (((String)e.getValue().get("COLLECTION")).equals(collectionId)) {
                return true;
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
    }

    public List<IRecord> getRecordsByUUID(UUID uuid) {
        return this.recordMap.entrySet().stream().filter(e -> {
            if (((UUID)e.getValue().get("UUID")).equals(uuid)) {
                return true;
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
    }

    @SuppressWarnings("unchecked")
    public List<IRecord> getRecordsByClassifier(String key, Object value) {
        return this.recordMap.entrySet().stream().filter(e -> {
            if (((Map<String,Object>)e.getValue().get("CLASSIFIERS")).keySet().contains(key)) {
                if (((List<Object>)((Map<String,Object>)e.getValue().get("CLASSIFIERS")).get(key)).contains(value)) {
                    return true;
                }
            }
            return false;
        }).map(e -> e.getKey()).collect(Collectors.toList());
    }

    public List<IRecord> getRecordsByTransformation(String transformationId) {
        //TODO: Complete method
        return this.getRecords();
    }

    private void setConnection(IConnection connection) {
        this.connection = connection;
    }

    private void setRecords(Map<IRecord, Map<String,Object>> recordMap) {
        this.recordMap = recordMap;
    }

}
