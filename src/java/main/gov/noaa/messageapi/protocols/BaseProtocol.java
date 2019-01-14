package gov.noaa.messageapi.protocols;

import java.util.Map;

public abstract class BaseProtocol {

    private String type;
    private Map<String, Object> properties;

    public BaseProtocol(Map<String, Object> properties) {
        setProperties(properties);
    }

    private void setProperties(Map<String, Object> properties) {
        this.properties = properties;
        setType((String) properties.get("type"));
    }

    private void setType(String type) {
        this.type = type.toLowerCase();
    }

    public String getType() {
        return this.type;
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
}
