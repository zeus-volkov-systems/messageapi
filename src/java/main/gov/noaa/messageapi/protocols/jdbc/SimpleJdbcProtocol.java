package gov.noaa.messageapi.protocols.jdbc;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.protocols.BaseProtocol;
import gov.noaa.messageapi.definitions.ProtocolDefinition;
import gov.noaa.messageapi.connections.rdbms.SimpleRdbmsConnection;

public class SimpleJdbcProtocol extends BaseProtocol implements IProtocol {

    private List<SimpleRdbmsConnection> connections = null;
    private static final Logger logger = LogManager.getLogger();

    public SimpleJdbcProtocol(Map<String, Object> properties) {
        super(properties);
    }

    public SimpleJdbcProtocol getCopy() {
        return this;
    }

    public void initialize(IContainer c, ISchema s){
        try {
            createConnections(createProtocolDefinition((String) getProperty("definitions")));
        } catch (Exception e) {
            logger.error("Could not initialize the protocol.");
        }
    }

    /*public void add(List<IContainerRecord> containerRecords) {
    }

    public void update(List<IContainerRecord> containerRecords) {
    }*/

    private ProtocolDefinition createProtocolDefinition(String protocolDefinitionSpec) throws Exception {
        return new ProtocolDefinition(protocolDefinitionSpec);
    }

    public List<SimpleRdbmsConnection> getConnections() {
        return this.connections;
    }

    private void createConnections(ProtocolDefinition p) {
        try {
            this.connections = p.connectionMaps.stream().map(m -> {
                {
                    try {
                        return new SimpleRdbmsConnection(m);
                    } catch (Exception e) {
                        logger.error("Error establishing connection for map: " + m);
                        return null;
                    }
                }
            }).collect(Collectors.toList());
        } catch (Exception e) {
            logger.error("Error establishing connections.");
        }
    }

}
