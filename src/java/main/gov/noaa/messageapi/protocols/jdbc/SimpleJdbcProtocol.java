package gov.noaa.messageapi.protocols.jdbc;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.protocols.BaseProtocol;

public class SimpleJdbcProtocol extends BaseProtocol implements IProtocol {


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
        } catch (Exception e) {}
    }

    public String getType() {
        return (String) this.definition.getMetadataMap().get("type");
    }

    public String getName() {
        return (String) this.definition.getMetadataMap().get("name");
    }


}
