package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IConnection;

public interface IProtocolRecord {

    public IConnection getConnection();
    public List<IRecord> getRecords();
    public List<IRecord> getRecordsByCollection(String collectionId);
    public List<IRecord> getRecordsByClassifier(String key, Object value);
    public List<IRecord> getRecordsByUUID(UUID uuid);
    public List<IRecord> getRecordsByTransformation(String transformationId);

}
