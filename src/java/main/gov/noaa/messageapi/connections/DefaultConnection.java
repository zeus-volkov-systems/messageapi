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
    private List<String> bins = null;
    private Map<String,List<Object>> classifiers = null;

    @SuppressWarnings("unchecked")
    public DefaultConnection(String endpointClass, Map<String,Object> connectionMap) throws Exception {
        super(endpointClass, (Map<String,Object>) connectionMap.get("parameters"));
        try {
            setId((String) connectionMap.get("id"));
            if (connectionMap.containsKey("bins")) {
                setBins(connectionMap.get("bins"));
            } else {
                setBins(new ArrayList<String>());
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

    public List<String> getBins() {
        return this.bins;
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
    private void setBins(Object bins) {
        if (bins instanceof String) {
            this.bins = new ArrayList<String>();
            this.bins.add((String) bins);
        } else if (bins instanceof List) {
            this.bins = (List<String>) bins;
        }
    }

    private void setClassifiers(Map<String,List<Object>> classifiers) {
        this.classifiers = classifiers;
    }
}
