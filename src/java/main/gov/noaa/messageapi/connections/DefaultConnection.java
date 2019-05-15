package gov.noaa.messageapi.connections;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.general.MapUtils;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.UUID;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.ITransformationFactory;

import gov.noaa.messageapi.utils.protocol.ConnectionUtils;

public class DefaultConnection extends BaseConnection implements IConnection {

    private String id;
    private List<String> collections = null;
    private Map<String,List<Object>> classifiers = null;
    private Map<String, Map<String, Object>> transformationMap = null;

    @SuppressWarnings("unchecked")
    public DefaultConnection(String endpointClass, Map<String,Object> connectionMap,
                             ITransformationFactory transformationFactory,
                             List<Map<String,Object>> rawTransformationMaps) throws Exception {
        super(endpointClass, (Map<String,Object>) connectionMap.get("constructor"));
        try {
            this.setId((String) connectionMap.get("id"));
            if (connectionMap.containsKey("collections")) {
                this.setCollections(connectionMap.get("collections"));
            } else {
                this.setCollections(new ArrayList<String>());
            }
            if (connectionMap.containsKey("classifiers")) {
                this.setClassifiers((Map<String,List<Object>>)connectionMap.get("classifiers"));
            } else {
                this.setClassifiers(new HashMap<String,List<Object>>());
            }
            if (connectionMap.containsKey("transformations")) {
                this.integrateTransformations((List<String>) connectionMap.get("transformations"), transformationFactory, rawTransformationMaps);
            } else {
                this.transformationMap = new HashMap<String, Map<String, Object>>();
            }
        } catch (Exception e) {
            System.out.println("Error in connection instantiation. Stacktrace to follow.");
            System.out.println(e.getStackTrace());
        }
    }

    public DefaultConnection(IConnection connection) throws Exception {
        super(connection);
        this.setId(connection.getId());
        this.setCollections(connection.getCollections());
        this.setClassifiers(connection.getClassifiers());
    }

    public DefaultConnection getCopy() {
        try {
            return new DefaultConnection(this);
        } catch (Exception e) {
            System.out.println("Failed copying connection, stacktrace follows.");
            e.printStackTrace();
            return null;
        }
    }


    public IPacket process(IProtocolRecord record) {
        return this.getEndpoint().process(record);
    }

    public String getId() {
        return this.id;
    }

    public List<String> getCollections() {
        return this.collections;
    }

    /**
     * Returns the list of classifiers that have been associated with this connection.
     * @return an arraylist containing every classifier associated with this connection.
     */
    public Map<String,List<Object>> getClassifiers() {
        return this.classifiers;
    }

    /**
     * Returns the transformation map of this connection. A transformation map contains
     * transformation ids as keys, each with an associated map value, where this
     * map value holds two string keys - instance, which contains a value of the
     * transformation instance, and args, which contains another map value,
     * containing process parameter keys (e.g., join_field_1) corresponding to a
     * stereotyped representation of the record set datatype it is eventually
     * meant to hold (eg, CLASSIFIER.CLASSKEY.CLASSVAL)
     * @return The transformation map associated with the connection.
     */
    public Map<String, Map<String,Object>> getTransformationMap() {
        return this.transformationMap;
    }

    /**
     * Returns all the classifier values for a specific classifier key
     * @param  classifierKey The particular classifier to return values for
     *                      (e.g., classifiers= [namespace], and ["namespace"] has "namespace1, namespace2")
     * @return               Outputs a list of classifiers for the provided key.
     */
    public List<Object> getClassiferValues(String classifierKey) {
        return this.classifiers.get(classifierKey);
    }

    private void setId(String id) {
        this.id = id + "_" + UUID.randomUUID().toString();
    }

    @SuppressWarnings("unchecked")
    private void setCollections(Object collections) {
        if (collections instanceof String) {
            this.collections = new ArrayList<String>();
            this.collections.add((String) collections);
        } else if (collections instanceof List) {
            this.collections = (List<String>) collections;
        }
    }

    /**
     * Sets the classifier set for this connection. Classifiers are held in
     * a map of classifier keys, each corresponding to a list value containing
     * an arbitrary number of unique classifier values to link records
     * @param classifiers
     */
    private void setClassifiers(Map<String,List<Object>> classifiers) {
        this.classifiers = classifiers;
    }

    /**
     * Adds new collections to the existing collections, ensuring there are no nulls
     * or duplicates
     * @param collections [description]
     */
    private void addCollections(List<String> collections) {
        List<List<String>> collectionLists = new ArrayList<List<String>>();
        collectionLists.add(this.getCollections());
        collectionLists.add(collections);
        this.setCollections(ListUtils.flatten(collectionLists));
    }

    /**
     * Adds new classifiers to the connection. Does this by merging new classifiers into old ones,
     * keeping all keys from both sets, while merging values of overlapping keys into a flat map
     * @param newClassifiers The new classifers to be added to the existing set
     */
    private void addClassifiers(Map<String,List<Object>> newClassifiers) {
        List<Map<String,List<Object>>> classifierMapList = new ArrayList<Map<String,List<Object>>>();
        classifierMapList.add(this.getClassifiers());
        classifierMapList.add(newClassifiers);
        this.setClassifiers(MapUtils.flattenValues(MapUtils.mergeMapsMergeValues(classifierMapList)));
    }

    private void integrateTransformations(List<String> transformations,
                                        ITransformationFactory transformationFactory,
                                        List<Map<String,Object>> rawTransformationMaps) {
        List<String> allTransformationIds = ConnectionUtils.getAllTransformationIds(transformations, rawTransformationMaps);
        //next, based on these transformation IDs, we need to update the collections that we will need for this connection.
        List<String> transformationCollections = ConnectionUtils.getTransformationCollections(allTransformationIds, rawTransformationMaps);
        this.addCollections(transformationCollections);
        //next, based on these transformation IDs, we need to update the classifiers that we will need for this connection.
        Map<String,List<Object>> transformationClassifiers = ConnectionUtils.getTransformationClassifiers(allTransformationIds, rawTransformationMaps);
        this.addClassifiers(transformationClassifiers);
        this.transformationMap = new HashMap<String,Map<String,Object>>();
    }
}
