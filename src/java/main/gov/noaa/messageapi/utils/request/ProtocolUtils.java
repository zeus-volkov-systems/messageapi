package gov.noaa.messageapi.utils.request;

import java.util.Map;
import java.util.List;
import java.util.UUID;
import java.util.HashMap;
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

    /**
     * Converts a list of containerized(factored into collections) records into
     * protocol records for use by endpoint connections. A protocol record
     * has a one to one relationship with a connection - i.e., there is one and
     * only one protocol record created for every connection held by the protocol
     * passed to this method.
     * @param  protocol         The protocol holding connection instances
     * @param  containerRecords A list of container Records to be parsed, categorized, and loaded into protocol records
     * @return                  A list of protocol records, one per connection
     */
    public static List<IProtocolRecord> convertContainerRecords(IProtocol protocol, List<IContainerRecord> containerRecords) {
        return protocol.getConnections().stream().map(conn -> {
            return createProtocolRecord(conn, containerRecords);
        }).collect(Collectors.toList());
    }

    /**
     * The singular method called by convertContainerRecords, accepts a single connection and a list of container records,
     * and creates a protocol record based on what the connection specified as data needs
     * @param  connection       A connection containing information on what type of records it needs (classifications, collections, transformations)
     * @param  containerRecords A list of container records that will be the basis for records added to the protocol record
     * @return                  A protocol record, containing a record map based on the containerRecords, for the given connection
     */
    public static IProtocolRecord createProtocolRecord(IConnection connection, List<IContainerRecord> containerRecords) {
        List<String> connCollections = connection.getCollections();
        Map<String,List<Object>> connClassifiers = connection.getClassifiers();
        List<Map<IRecord, Map<String,Object>>> recordList = ListUtils.flatten(containerRecords.stream().map(containerRecord -> {
            UUID recordId = containerRecord.getId();
            return ListUtils.removeAllNulls(containerRecord.getCollections().stream().map(collection -> {
                return convertCollectionToRecord(collection, recordId, connCollections, connClassifiers);
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList()));
        return new ProtocolRecord(connection, MapUtils.mergeMapList(recordList));
    }

    /**
     * Creates a new collection record map entry for the IProtocolRecord map. This entry has a key of
     * the record itself (created from the collection field set),
     * with a map value, that itself has keys of UUID (uuid type), COLLECTION (string collID), and CLASSIFIERS (Map<String, Object>).
     *
     * @param  collection      The collection that will serve as the basis for the record (record uses collection fields)
     * @param  recordId        A record ID to associated with this record - the UUID of the container it came from
     * @param  connCollections A list of collections referenced by a connection that will be used to
     * determine if this record fits in the given record
     * @param  connClassifiers A map of classifiers referenced by a connection that this record will be attached to
     * @return                 A new map consisting of a record (IRecord) and a set of associated properties (in a map).
     * If none of the properties match, this method returns null.
     */
    public static Map<IRecord, Map<String,Object>> convertCollectionToRecord(ICollection collection, UUID recordId,
                                                        List<String> connCollections, Map<String,List<Object>> connClassifiers) {
        String collectionId = collection.getId();
        Map<String, Object> collectionClassifiers = collection.getClassifiers();
        if (collectionMatch(collectionId, connCollections) || classifierMatch(collectionClassifiers, connClassifiers)) {
            return makeCollectionRecordMap(recordId, new SchemaRecord(collection.getFields()), collectionId, collectionClassifiers);
        }
        return null;
    }

    /**
     * Creates a record map for the given record. This record map will be one of many that are merged into
     * a single record map for the ProtocolRecord (one map per protocol record). This map
     * associates the record object (as a key) with a map of associated properties (as the value).
     * These properties included the UUID of the ancestral container, the collectionId of the collection which
     * was used in the record creation, and a map of classifiers (key/value pairs) that categorize the record.
     * Please note - that in general, objects are not good candidates for map keys, due to key operations being
     * indeterminate if objects are changed. However, in this case, we use the value map as the search criteria.
     * The record as the key is what's used in processing if some value map parameter matches, making this pattern
     * unconcerned with holding the record as a map key.
     * @param  id           A UUID belonging to the parent container (all collections get the same UUID)
     * @param  record       A record created from the collection field set
     * @param  collectionId The id (string) of the collection used to create the record
     * @param  classifiers  A map of classifiers that
     * @return              a map for the record
     */
    public static Map<IRecord,Map<String,Object>> makeCollectionRecordMap(UUID id, IRecord record, String collectionId, Map<String,Object> classifiers) {
        Map<IRecord,Map<String,Object>> retMap = new HashMap<IRecord, Map<String,Object>>();
        Map<String, Object> valMap = new HashMap<String, Object>();
        valMap.put("UUID", id);
        valMap.put("COLLECTION", collectionId);
        valMap.put("CLASSIFIERS",classifiers);
        retMap.put(record, valMap);
        return retMap;
    }

    /**
     * Determines if a collection ID is contained within a connection list of
     * associated collections (or if the connection wants all collections) and returns
     * a boolean indicating true (if it matches) or false in the negative case
     * @param  collectionId    An id of the collection in question
     * @param  connCollections A list of collection ids associated with a given connection
     * @return                 true if a match, otherwise false
     */
    public static Boolean collectionMatch(String collectionId, List<String> connCollections) {
        if (connCollections.contains(collectionId) || connCollections.contains("*")) {
            return true;
        }
        return false;
    }

    /**
     * Determines if a given collection classifier matches any of the associated classifiers
     * referenced by a connection. This method first checks for classifier key matches,
     * and then for any matching key, checks the value. Returns true if a match, otherwise false
     * @param  collectionClassifiers A set of classifiers attached to the collection
     * @param  connClassifiers       A set of classifers attached to the connection
     * @return                       true if classifiers match, false otherwise
     */
    public static Boolean classifierMatch(Map<String,Object> collectionClassifiers, Map<String,List<Object>> connClassifiers) {
        List<String> matchKeys = ListUtils.removeAllNulls(collectionClassifiers.keySet().stream().filter(key -> connClassifiers.keySet().contains(key)).collect(Collectors.toList()));
        if (classifierValueMatch(matchKeys, collectionClassifiers, connClassifiers)) {
            return true;
        }
        return false;
    }

    @SuppressWarnings("unchecked")
    /**
     * Determines if a collection classifier belongs to a connection classifier.
     * Returns true if it matches, false otherwise
     * @param  keys                  A set of keys that match both connection and collection,
     * each key corresponding to a singular or list value of classifier values
     * @param  collectionClassifiers A map of the classifiers in the target collection
     * @param  connClassifiers       A map of classifiers in the comparison connection
     * @return                       returns true if the classifier pair is a match, false otherwise
     */
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
