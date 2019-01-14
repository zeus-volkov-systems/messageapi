package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.parsers.ProtocolDefinitionParser;

/**
 * A protocol definition holds the definition of a protocol. It essentially
 * acts as a blueprint for use by instantiated protocols, separating out
 * what a protocol is from how it is used. Protocol Definitions hold things
 * like protocol record definitions, connection info, etc. as maps.
 * This class is used by the session factory to bootstrap new protocols
 * from a configurable specification.
 */
public class ProtocolDefinition {

    public List<Map<String,Object>> connectionMaps = null;

    public ProtocolDefinition(String spec) throws Exception {
        parseProtocolDefinitionSpec(spec);
    }

    private void parseProtocolDefinitionSpec(String spec) throws Exception {
        this.connectionMaps = new ProtocolDefinitionParser(spec).getConnectionMaps();
    }

}
