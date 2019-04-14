package gov.noaa.messageapi.connections;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public class DefaultConnection extends BaseConnection implements IConnection {

    private String id;
    private List<String> collections = null;
    private Map<String,List<Object>> classifiers = null;

    @SuppressWarnings("unchecked")
    public DefaultConnection(String endpointClass, Map<String,Object> connectionMap) throws Exception {
        super(endpointClass, (Map<String,Object>) connectionMap.get("parameters"));
        try {
            setId((String) connectionMap.get("id"));
            if (connectionMap.containsKey("collections")) {
                setCollections(connectionMap.get("collections"));
            } else {
                setCollections(new ArrayList<String>());
            }
            if (connectionMap.containsKey("classifiers")) {
                setClassifiers((Map<String,List<Object>>)connectionMap.get("classifiers"));
            } else {
                setClassifiers(new HashMap<String,List<Object>>());
            }
        } catch (Exception e) {
            System.out.println("Error in connection instantiation. Stacktrace to follow.");
            System.out.println(e.getStackTrace());
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
     * Returns all the classifier values for a specific classifier key
     * @param  classifierKey The particular classifier to return values for
     *                      (e.g., classifiers= [namespace], and ["namespace"] has "namespace1, namespace2")
     * @return               Outputs a list of classifiers for the provided key.
     */
    public List<Object> getClassiferValues(String classifierKey) {
        return this.classifiers.get(classifierKey);
    }

    private void setId(String id) {
        this.id = id;
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

    private void setClassifiers(Map<String,List<Object>> classifiers) {
        this.classifiers = classifiers;
    }
}
