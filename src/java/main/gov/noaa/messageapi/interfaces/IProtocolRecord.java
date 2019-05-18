package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.UUID;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;

public interface IProtocolRecord {

    public String getConnectionId();
    public Map<String, Map<String,Object>> getTransformationMap();
    public Map<IRecord,Map<String,Object>> getRecordMap();
    public List<IRecord> getRecords();
    public List<IRecord> getRecordsByCollection(String collectionId);
    public List<IRecord> getRecordsByClassifier(String key, Object value);
    public List<IRecord> getRecordsByUUID(UUID uuid);
    public List<IRecord> getRecordsByTransformation(String transformationId);

}
