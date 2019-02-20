package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import gov.noaa.messageapi.parsers.protocols.MetadataParser;
import gov.noaa.messageapi.parsers.protocols.ConnectionParser;

/**
 * A protocol definition holds the definition of a protocol. It essentially
 * acts as a blueprint for use by instantiated protocols, separating out
 * what a protocol is from how it is used. Protocol Definitions hold things
 * like protocol record definitions, connection info, etc. as maps.
 * This class is used by the session factory to bootstrap new protocols
 * from a configurable specification.
 */
public class ProtocolDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> connectionMaps = null;
    private String endpoint = null;

    public ProtocolDefinition(Map<String,Object> properties) throws Exception {
        parseMetadataSpec((String) properties.get("metadata"));
        parseConnectionSpec((String) properties.get("connections"));
        parseEndpoint((String) properties.get("endpoint"));
    }

    public ProtocolDefinition(ProtocolDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.connectionMaps = new ArrayList<Map<String,Object>>(definition.getConnectionMaps());
        this.endpoint = definition.getEndpoint();
    }

    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    private void parseConnectionSpec(String spec) throws Exception {
        ConnectionParser parser = new ConnectionParser(spec);
        this.connectionMaps = parser.getConnectionMaps();
    }

    private void parseEndpoint(String endpoint) throws Exception {
        this.endpoint = endpoint;
    }

    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    public List<Map<String,Object>> getConnectionMaps() {
        return this.connectionMaps;
    }

    public String getEndpoint() {
        return this.endpoint;
    }

}
