package gov.noaa.messageapi.protocols.jdbc;

import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.protocols.BaseProtocol;

public class SimpleJdbcProtocol extends BaseProtocol implements IProtocol {

    private static final Logger logger = LogManager.getLogger();

    public SimpleJdbcProtocol(Map<String, Object> properties) {
        super(properties);
    }

    public SimpleJdbcProtocol(IProtocol protocol) {
        super(protocol);
    }

    public IProtocol getCopy() {
        return new SimpleJdbcProtocol(this);
    }

    public void initialize(IContainer c, ISchema s){
        try {
            this.createProtocolDefinition(this.getProperties());
        } catch (Exception e) {
            logger.error("Could not initialize the protocol.");
        }
    }

    public String getType() {
        return (String) this.definition.getMetadataMap().get("type");
    }

    public String getName() {
        return (String) this.definition.getMetadataMap().get("name");
    }


}
