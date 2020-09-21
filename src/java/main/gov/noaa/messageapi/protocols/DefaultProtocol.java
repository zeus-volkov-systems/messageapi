package gov.noaa.messageapi.protocols;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IConnection;

import gov.noaa.messageapi.metadata.DefaultMetadata;
import gov.noaa.messageapi.connections.DefaultConnection;
import gov.noaa.messageapi.definitions.ContainerDefinition;
import gov.noaa.messageapi.utils.general.ListUtils;

/**
 * The default protocol wraps arbitrary number of endpoints, each referencing
 * an arbitrary number of connections. Each connection to each endpoint is a separate object.
 * The default protocol also contains a Metadata object to allow tracking of information
 *  relevant to quality control of this class.
 *  @author Ryan Berkheimer
 */
public class DefaultProtocol extends BaseProtocol implements IProtocol {

    List<IConnection> connections = null;

    /**
     * The default constructor for a protocol - used to construct a default protocol
     * from a specification map (JSON) to in-memory data structures (hash map, list)
     * and validate it. This constructor is generally called when sessions
     * are being created. There is an associated method - initialize - that
     * is called by the user of this constructor. The initialize method is called separately
     * to allow for use of schema or container properties in protocol initialization if
     * required or convenient.
     * @param protocolMap A protocol map containing the information model specification
     * used to construct a Protocol.
     */
    public DefaultProtocol(final Map<String, Object> protocolMap) {
        super(protocolMap);
    }

    /**
     * Request Constructor for the Default Protocol - used when creating a Request
     * from a session. First creates the definition (parses text docs to in-memory
     * data structures) and then sets metadata object and instantiates connection
     * objects.
     * 
     * @param protocol The protocol
     * @throws Exception [description]
     */
    public DefaultProtocol(final IProtocol protocol) throws Exception {
        super(protocol);
        this.setMetadata(protocol.getDefinition().getMetadataMap());
        this.setConnections(protocol.getConnections());
    }

    /**
     * A method used to duplicate the protocol it's called on - this allows requests
     * to use the same protocol, but get their own copy, ensuring immutability in
     * request generation, and thus providing for library use in parallel contexts
     * (parallel requests in different threads).
     * 
     * @return Returns a deep-copy of this protocol.
     */
    public IProtocol getCopy() {
        try {
            return new DefaultProtocol(this);
        } catch (final Exception e) {
            return null;
        }
    }

    /**
     * Initializes this protocol object - this involves conversion of generic data
     * structures (hash maps, lists) to object structures (e.g, a metadata
     * object,connection objects). Passes associated container and schema objects
     * in, in case there is something on those objects that needs to be used in
     * initialization of this protocol object.
     * 
     * @param c A container instance (implementation of the IContainer interface)
     * @param s A schema instance (implementation of the ISchema interface)
     */
    public void initialize(final IContainer c, final ISchema s) {
        try {
            this.createProtocolDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
            this.setConnections(this.definition.getEndpointMap(), c.getDefinition());
        } catch (final Exception e) {
        }
    }

    /**
     * Returns the connection objects stored in this protocol. Connections for any
     * endpoint are all stored in a flat list (the returned list). These are actual
     * implementations of the IConnection protocol (they are already instantiated
     * connections).
     * 
     * @return A list of connection objects owned by this protocol.
     */
    public List<IConnection> getConnections() {
        return this.connections;
    }

    /**
     * Returns the protocol type - this currently returns a string providing the
     * name "DefaultProtocol". This is a legacy method from early package
     * development, and is a probable candidate for deprecation unless its utility
     * is proven.
     * 
     * @return A string equivalent to "DefaultProtocol"
     */
    public String getType() {
        return "DefaultProtocol";
    }

    /**
     * Creates a metadata object and attaches to the protocol from a metadataMap.
     * The metadata map contains information related to tracking of this protocol,
     * including versioning, tagging, and other meta information. This information
     * is useful in a couple of ways. First, due to the nature of MessageAPI in that
     * this class is a plugin to the system, the information in the MetaData object
     * may be used for validation and class type safety checks (data/security
     * validation, quality control, etc.) Second, this metadata object may be useful
     * in the case that sessions are ever build dynamically, through some external
     * UI - a library of Protocols may be available for selection.
     * 
     * @param metadataMap A map containing key/value pairs used to construct the
     *                    metadata object.
     */
    private void setMetadata(final Map<String, Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

    /**
     * Instantiates connection objects and adds them to this protocol's connection
     * list. Connection objects are built using the protocol's definition connection
     * map.
     * 
     * @param endpointMap The endpoint map containing entries where k is endpoint
     *                    string and v is a map of all connection specs for that
     *                    particular endpoint.
     * @throws Exception Throws an exception in the case that connections are not
     *                   successfully created or added to the protocol
     */
    private void setConnections(final Map<String, List<Map<String, Object>>> endpointMap,
            final ContainerDefinition containerDefinition) throws Exception {
        this.connections = ListUtils.flatten(endpointMap.entrySet().stream().map(entry -> {
            final String plugin = entry.getKey();
            return ListUtils.removeAllNulls(entry.getValue().stream().map(connectionMap -> {
                try {
                    return (IConnection) new DefaultConnection(plugin, (Map<String, Object>) connectionMap,
                            containerDefinition);
                } catch (final Exception e) {
                    return null;
                }
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList()));
    }

    /**
     * Sets this protocols connections collection to a deep-copied set of the passed
     * connection set. This method is primarily used during request building to
     * ensure immutability in the case of threaded operation.
     * 
     * @param connections A list of connections to deep-copy
     */
    private void setConnections(final List<IConnection> connections) {
        this.connections = ListUtils.removeAllNulls(connections.stream().map(conn -> {
            return conn.getCopy();
        }).collect(Collectors.toList()));
    }

}
