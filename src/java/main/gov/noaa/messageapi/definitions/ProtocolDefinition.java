package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.AbstractMap;

import java.util.stream.Collectors;

import gov.noaa.messageapi.parsers.protocols.MetadataParser;
import gov.noaa.messageapi.parsers.protocols.ConnectionParser;

import gov.noaa.messageapi.utils.general.ListUtils;

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
    private Map<String,List<Map<String,Object>>> endpointMap = null;

    @SuppressWarnings("unchecked")
    public ProtocolDefinition(Map<String,Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            this.parseMetadataSpec((String) properties.get("metadata"));
        } else {
            throw new Exception("Missing necessary 'metadata' key when parsing protocol definition.");
        }
        if (properties.containsKey("endpoints")) {
            this.parseEndpoints((List<Map<String,String>>) properties.get("endpoints"));
        } else {
            throw new Exception("Missing necessary 'endpoint' key when parsing protocol definition.");
        }
    }

    public ProtocolDefinition(ProtocolDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.endpointMap = new HashMap<String, List<Map<String,Object>>>(definition.getEndpointMap());
    }

    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    /**
     * Takes a list of endpoint entries from the global session spec and converts
     * them to a single endpoint map, where endpoint classes point to a list of
     * their connection class maps.
     * @param  endpoints A list of endpoint entries that contain pointers to endpoint classes and a location of their connection maps.
     * @throws Exception Throws an exception if there's a failure when constructing the ProtocolDefinition endpoint map.
     */
    private void parseEndpoints(List<Map<String,String>> endpoints) throws Exception {
        this.endpointMap = new HashMap<String,List<Map<String,Object>>>();
        ListUtils.removeAllNulls(endpoints.stream().map(endpointMap -> {
            if (endpointMap.containsKey("plugin")) {
                if (endpointMap.containsKey("connections")) {
                    try {
                        ConnectionParser connParser = new ConnectionParser(endpointMap.get("connections"));
                        return new AbstractMap.SimpleEntry<String, List<Map<String,Object>>>
                            ((String) endpointMap.get("plugin"),
                            (List<Map<String,Object>>) connParser.getConnectionMaps());
                    } catch (Exception e) {
                        return null;
                    }
                }
            }
            return null;
        }).collect(Collectors.toList()))
            .stream()
            .forEach(endpointMapEntry -> this.endpointMap.put(endpointMapEntry.getKey(),
                                                        endpointMapEntry.getValue()));
    }

    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    public Map<String,List<Map<String,Object>>> getEndpointMap() {
        return this.endpointMap;
    }

}
