package gov.noaa.messageapi.protocols.jdbc;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;

import gov.noaa.messageapi.protocols.BaseProtocol;
import gov.noaa.messageapi.metadata.DefaultMetadata;

public class SimpleJdbcProtocol extends BaseProtocol implements IProtocol {

    public SimpleJdbcProtocol(Map<String, Object> properties) {
        super(properties);
    }

    public SimpleJdbcProtocol(IProtocol protocol) {
        super(protocol);
        this.setMetadata(protocol.getDefinition().getMetadataMap());
    }

    public IProtocol getCopy() {
        return new SimpleJdbcProtocol(this);
    }

    public void initialize(IContainer c, ISchema s){
        try {
            this.createProtocolDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
        } catch (Exception e) {}
    }

    public String getType() {
        return "SimpleJdbcProtocol";
    }

    private void setMetadata(Map<String,Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

}
