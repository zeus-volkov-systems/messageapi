package gov.noaa.messageapi.protocols;

import java.util.Map;
import java.util.HashMap;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IMetadata;
import gov.noaa.messageapi.definitions.ProtocolDefinition;


/**
 * @author Ryan Berkheimer
 */
public class BaseProtocol {

    private Map<String, Object> properties;
    protected ProtocolDefinition definition;
    protected IMetadata metadata = null;

    public BaseProtocol(Map<String, Object> properties) {
        this.setProperties(properties);
    }

    public BaseProtocol(IProtocol protocol) {
        this.definition = new ProtocolDefinition(protocol.getDefinition());
        this.properties = new HashMap<String,Object>(protocol.getProperties());
    }

    private void setProperties(Map<String, Object> properties) {
        this.properties = properties;
    }

    public Map<String,Object> getProperties() {
        return this.properties;
    }

    public Object getProperty(String key) {
        if (hasProperty(key)) {
            return this.properties.get(key);
        }
        return null;
    }

    public boolean hasProperty(String key) {
        if (this.properties.containsKey(key)) {
            return true;
        }
        return false;
    }

    public ProtocolDefinition getDefinition() {
        return this.definition;
    }

    public IMetadata getMetadata() {
        return this.metadata;
    }

    protected void createProtocolDefinition(Map<String,Object> properties) throws Exception {
        this.definition = new ProtocolDefinition(properties);
    }

}
