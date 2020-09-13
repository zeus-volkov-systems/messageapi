package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.AbstractMap;

import java.util.stream.Collectors;

import gov.noaa.messageapi.parsers.protocols.MetadataParser;
import gov.noaa.messageapi.parsers.protocols.ConnectionParser;
import gov.noaa.messageapi.parsers.protocols.EndpointParser;
import gov.noaa.messageapi.utils.general.ListUtils;

/**
 * A protocol definition holds the definition of a protocol. It essentially
 * acts as a blueprint for use by instantiated protocols, separating out
 * what a protocol is from how it is used. Protocol Definitions hold things
 * like protocol record definitions, connection info, etc. as maps.
 * This class is used by the session factory to bootstrap new protocols
 * from a configurable specification.
 * @author Ryan Berkheimer
 */
public class ProtocolDefinition {

    private Map<String,Object> metadataMap = null;
    private Map<String,List<Map<String,Object>>> endpointMap = null;

    public ProtocolDefinition(Map<String,Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            this.parseMetadataSpec((String) properties.get("metadata"));
        } else {
            this.setEmptyMetadata();
        }
        if (properties.containsKey("endpoints")) {
            this.parseEndpoints(properties.get("endpoints"));
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
     * 
     * @param endpointSpec A spec that is used to determine how to parse the session endpoints, either through a path or a direct map
     * @throws Exception
     */
    private void parseEndpoints(Object endpoints) throws Exception {
        this.endpointMap = new HashMap<String,List<Map<String,Object>>>();
        try {
            if (endpoints instanceof String) {
                this.parseEndpointsFromSpec((String) endpoints);
            } else if (endpoints instanceof List) {
                this.parseEndpointsFromManifest((List<Map<String,String>>) endpoints);
            }
            if (this.endpointMap.isEmpty()) {
                System.err.println("After endpoint parsing, there are no endpoints. Nowhere to send data, so killing session before creation.");
                System.exit(1);
            }
        } catch (Exception e) {
            System.out.println("The endpoint specification was an invalid data structure Needs to be list or map.");
            System.err.println("The protocol layer must contain a valid endpoint. Ending session building now.");
            System.exit(1);
        }
    }

    private void parseEndpointsFromSpec(String endpointSpec) throws Exception {
        EndpointParser endpointParser = new EndpointParser(endpointSpec);
        ListUtils.removeAllNulls(endpointParser.getEndpointMaps().stream().map(endpointMap -> {
            if (endpointMap.containsKey("plugin")) {
                if (endpointMap.containsKey("connections")) {
                    try {
                        return new AbstractMap.SimpleEntry<String, List<Map<String,Object>>>
                        ((String)endpointMap.get("plugin"), (List<Map<String,Object>>)endpointMap.get("connections"));
                    } catch (Exception e) {
                        System.err.println("Warning - malformed endpoint spec (it will not get data, but this does not crash the session if there are other endpoints).");
                        System.err.println(String.format("Check formatting of the %s endpoint connections",(String) endpointMap.get("plugin")));
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

    /**
     * Takes a list of endpoint entries from the global session spec and converts
     * them to a single endpoint map, where endpoint classes point to a list of
     * their connection class maps.
     * @param  endpoints A list of endpoint entries that contain pointers to endpoint classes and a location of their connection maps.
     * @throws Exception Throws an exception if there's a failure when constructing the ProtocolDefinition endpoint map.
     */
    private void parseEndpointsFromManifest(List<Map<String,String>> endpoints) throws Exception {
        ListUtils.removeAllNulls(endpoints.stream().map(endpointMap -> {
            if (endpointMap.containsKey("plugin")) {
                if (endpointMap.containsKey("connections")) {
                    try {
                        ConnectionParser connParser = new ConnectionParser(endpointMap.get("connections"));
                        return new AbstractMap.SimpleEntry<String, List<Map<String,Object>>>
                            ((String) endpointMap.get("plugin"),
                            (List<Map<String,Object>>) connParser.getConnectionMaps());
                    } catch (Exception e) {
                        System.err.println("Warning - malformed endpoint spec (it will not get data, but this does not crash the session if there are other endpoints).");
                        System.err.println(String.format("Check formatting of the  %s endpoint",(String) endpointMap.get("plugin")));
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

    /**
     * sets empty metadata on the definition, in the case that we aren't using
     * metadata.
     */
    private void setEmptyMetadata() throws Exception {
        this.metadataMap = new HashMap<String, Object>();
    }

}
