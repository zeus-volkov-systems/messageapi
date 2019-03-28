package gov.noaa.messageapi.connections;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IContainerRecord;


public class DefaultConnection extends BaseConnection implements IConnection {

    private String id;
    private List<String> bins = null;
    private Map<String,List<String>> classifiers = null;

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
                setClassifiers((Map<String,List<String>>)connectionMap.get("classifiers"));
            } else {
                setClassifiers(new HashMap<String,List<String>>());
            }
        } catch (Exception e) {
            System.out.println("Error in connection instantiation. Stacktrace to follow.");
            System.out.println(e.getStackTrace());
        }
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
    public List<String> getClassifiers() {
        return new ArrayList<>(this.classifiers.keySet());
    }

    /**
     * Returns all the classifier values for a specific classifier key
     * @param  classifierKey The particular classifier to return values for
     *                      (e.g., classifiers= [namespace], and ["namespace"] has "namespace1, namespace2")
     * @return               Outputs a list of classifiers for the provided key.
     */
    public List<String> getClassifers(String classifierKey) {
        return this.classifiers.get(classifierKey);
    }

    public IProtocolRecord process(List<IContainerRecord> containerRecords) {
        return this.getEndpoint().process(containerRecords);
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

    private void setClassifiers(Map<String,List<String>> classifiers) {
        this.classifiers = classifiers;
    }
}
