package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.UUID;
import java.util.List;


/**
 * ProtocolRecords are one-to-one matches with Endpoint Connections.
 * ProtocolRecords are primarily responsible for holding a transformation-map,
 * with Record objects and their associated Transformations, Collections,
 * and Classifiers that were specified as being associated with the Connection.
 * In a given Endpoint Connection, this ProtocolRecord can be called on to
 * produce the results (always as a List<IRecord>) of whatever container is retrieved.
 * In a given request, this typically happens lazily - i.e. any computation is done
 * when requested and not before.
 * @author Ryan Berkheimer
 */
public interface IProtocolRecord {

    /**
     * Returns the ID of the connection for which this Protocol Record is associated.
     * ConnectionIDs are globally unique within the context of a Session. Only
     * one connection is associated with one protocol record.
     */
    public String getConnectionId();

    /**
     * Returns the transformation map held by this connection. The transformation map holds
     * transformations that were defined in the connection spec in the session manifest. Each
     * entry holds the information needed to apply a transformation to a passed record set.
     */
    public Map<String, Map<String,Object>> getTransformationMap();

    /**
     * The record map holds key/value pairs with record objects as the key and
     * another map as the value. This value map holds all associated collections,
     * classifiers, and transformations that are both associated with the connection
     * and the record instance. This map makes record retrieval possible.
     */
    public Map<IRecord,Map<String,Object>> getRecordMap();

    /**
     * Returns all records associated with the connection that are held in the record map.
     */
    public List<IRecord> getRecords();

    /**
     * Returns all records associated with the named collection.
     * 
     */
    public List<IRecord> getRecordsByCollection(String collectionId);

    /**
     * Returns all records associated with the named classifier. Classifiers
     * hold both keys and values, both must be provided.
     */
    public List<IRecord> getRecordsByClassifier(String key, Object value);

    /**
     * Returns all records for the specified UUID. 
     */
    public List<IRecord> getRecordsByUUID(UUID uuid);

    /**
     * Returns all records for the specified UUID (used for uuid as string).
     */
    public List<IRecord> getRecordsByUUID(String uuid);

    /**
     * Returns all records for the specified transformation. This will apply the
     * transformation when called, in turn calling any other transformation that
     * this transformation might reference as an input.
     */
    public List<IRecord> getRecordsByTransformation(String transformationId);

}
