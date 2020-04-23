package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

/**
 * An IConnection is an instantiation of an IEndpoint - 
 * Connections are provided specific versions of the Endpoint
 * required initialization parameters, and a separate object
 * is created for every Connection in the session manifest.
 * Connections contain metadata related to Endpoint instances,
 * including what classifiers, collections, and transformations
 * are associated with the Endpoint.
 * 
 * Connections should have globally unique Ids for a given
 * session manifest.
 * @author Ryan Berkheimer
 */
public interface IConnection {

    /**
     * Returns the ID associated with the Connection
     */
    public String getId();

    /**
     * Returns a list of the collections associated with the Connection.
     */
    public List<String> getCollections();

    /**
     * Returns a map of classifiers associated with the Connection.
     */
    public  Map<String,List<Object>> getClassifiers();

    /**
     * Returns a map of transformations associated with the Connection.
     * This map includes the transformation ids along with their connection
     * parameters. 
     */
    public Map<String, Map<String,Object>> getTransformationMap();

    /**
     * Returns all values for a given classifier key in the connection
     * classifier map.
     */
    public List<Object> getClassiferValues(String classifierKey);

    /**
     * Returns the EndpointClass used to initialize the endpoint connection.
     * This class is a fully qualified, namespaced class on the Java classpath.
     */
    public String getEndpointClass();

    /**
     * Returns a map of constructor parameters used to initialize
     * the endpoint constructor.
     */
    public Map<String,Object> getEndpointConstructor();

    /**
     * The method that is called when the request is submitted
     * and the endpoint connection is called into. This method
     * takes a protocol record (one to one association with the connection)
     * and returns a packet.
     */
    public IPacket process(IProtocolRecord record);

    /**
     * Returns a deep copy of the Connection
     */
    public IConnection getCopy();

}
