package gov.noaa.messageapi.records.protocol;

import java.util.UUID;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public class ProtocolRecord implements IProtocolRecord {

    private String connection;
    private Map<IRecord,Map<String,Object>> recordMap;

    public ProtocolRecord(String connection,
                          Map<IRecord, Map<String,Object>> recordMap) {
        this.setConnection(connection);
        this.setRecords(recordMap);
    }

    public String getConnection(){
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
        //we will need available - a map of transformations (transformation ID as key, transformation object instance as value)
        //A transformation object has a process method and a describe method. The describe method should return a map containing
        //keys that we need to provide. Keys should be record sets. We can then pull the record sets out of the record map and process
        //these records according to the transformation. E.g., our transformation ID key corresponds to an instance value that returns,
        //from the transformation describe method, a map containing keys "1", "2", "3" with values "classifier=x.a, classifer=y.b, collection=z", transformation="t".
        //Based on these, we can create a new map (with keys 1, 2, 3) and replace the values with copies of the record sets corresponding
        //to that request. We turn the {1: {classifier: [key,val]}, 2: {classifier: [key,val]}, 3: {collection: id}} map into one with the actual
        //record call (this can be acquired by iterating over map keys, inspecting the map value, and making the appropriate call on the protocol record).
        //We then call process() or apply() on the transformation object with this updated map. That method will then apply it's transformation as specified
        //and return an updated set of records.
        return this.getRecords();
    }

    private void setConnection(String connection) {
        this.connection = connection;
    }

    private void setRecords(Map<IRecord, Map<String,Object>> recordMap) {
        this.recordMap = recordMap;
    }

}
