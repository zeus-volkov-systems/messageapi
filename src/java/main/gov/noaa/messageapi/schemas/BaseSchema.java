package gov.noaa.messageapi.schemas;

import java.util.Map;
import java.util.HashMap;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IMetadata;
import gov.noaa.messageapi.definitions.SchemaDefinition;


/**
 * @author Ryan Berkheimer
 */
public class BaseSchema {

    private Map<String, Object> properties = null;
    protected SchemaDefinition definition = null;
    protected IMetadata metadata = null;


    public BaseSchema(Map<String, Object> properties) {
        setProperties(properties);
    }

    public BaseSchema(ISchema schema) {
        this.definition = new SchemaDefinition(schema.getDefinition());
        this.properties = new HashMap<String,Object>(schema.getProperties());
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

    public SchemaDefinition getDefinition() {
        return this.definition;
    }

    public IMetadata getMetadata() {
        return this.metadata;
    }

    protected void createSchemaDefinition(Map<String,Object> properties) throws Exception {
        this.definition = new SchemaDefinition(properties);
    }

}
