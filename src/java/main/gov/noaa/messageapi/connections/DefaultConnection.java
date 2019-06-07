package gov.noaa.messageapi.connections;

import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.UUID;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.ITransformationFactory;

import gov.noaa.messageapi.definitions.ContainerDefinition;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.general.MapUtils;
import gov.noaa.messageapi.utils.protocol.ConnectionUtils;

/**
 * @author Ryan Berkheimer
 */
public class DefaultConnection extends BaseConnection implements IConnection {

    private String id;
    private List<String> collections = null;
    private Map<String,List<Object>> classifiers = null;
    private Map<String, Map<String, Object>> transformationMap = null;

    @SuppressWarnings("unchecked")
    public DefaultConnection(String endpointClass, Map<String,Object> connectionMap,
                ContainerDefinition containerDefinition) throws Exception {
        super(endpointClass, connectionMap, containerDefinition);
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
                this.integrateTransformations((List<String>) connectionMap.get("transformations"),
                                containerDefinition.getTransformationFactory(), containerDefinition.getTransformationMaps());
            } else {
                this.setTransformationMap(new HashMap<String, Map<String, Object>>());
            }
        } catch (Exception e) {
            throw new InstantiationException(String.format("Error in instantiating connection with class %s, connectionMap %s",
                        endpointClass,connectionMap));
        }
    }

    public DefaultConnection(IConnection connection) throws Exception {
        super(connection);
        try {
            this.setId(connection.getId());
            this.setCollections(connection.getCollections());
            this.setClassifiers(connection.getClassifiers());
            this.setTransformationMap(connection.getTransformationMap());
        } catch (Exception e) {
            throw new InstantiationException("Error in instantiating new connection from existing connection");
        }
    }

    public DefaultConnection getCopy() {
        try {
            return new DefaultConnection(this);
        } catch (Exception e) {
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
     * meant to hold (eg, CLASSIFIER=CLASSKEY.CLASSVAL)
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

    private void setTransformationMap(Map<String, Map<String, Object>> transformationMap) {
        this.transformationMap = transformationMap;
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

    /**
     * Integrates transformations into the connection. Integration in this context means
     * updating the connection with all information required to eventually apply the transformations
     * associated with it during endpoint processing. Things added to the connection during integration
     * are parent transformations of named transformations, as well as classifiers and connections
     * used by any transformation.
     * @param transformations       The named transformations included on the connection spec itself
     * @param transformationFactory A class factory that contains key/value pairs of transformation operator keywords and class references
     * @param rawTransformationMaps The raw transformation maps containing entire transformation specifications
     */
    private void integrateTransformations(List<String> transformations,ITransformationFactory transformationFactory, List<Map<String,Object>> rawTransformationMaps) {
        List<String> allTransformationIds = ConnectionUtils.getAllTransformationIds(transformations, rawTransformationMaps);
        List<String> transformationCollections = ConnectionUtils.getTransformationCollections(allTransformationIds, rawTransformationMaps);
        Map<String,List<Object>> transformationClassifiers = ConnectionUtils.getTransformationClassifiers(allTransformationIds,
                                                                rawTransformationMaps);
        Map<String, Map<String, Object>> transformationMap = ConnectionUtils.buildTransformationMap(allTransformationIds,
                                                                rawTransformationMaps, transformationFactory);
        this.addCollections(transformationCollections);
        this.addClassifiers(transformationClassifiers);
        this.setTransformationMap(transformationMap);
    }
}
