package gov.noaa.messageapi.metadata;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IMetadata;

/**
 * Metadata contains useful information regarding a specific plugin.
 * This can be used to provide context to a plugin, track schema changes
 * over time (like the Avro library), or otherwise automate/simplify plugin
 * use for library developers and users.
 * @author Ryan Berkheimer
 */
public class DefaultMetadata implements IMetadata {

    private String id = null;
    private Object version = null;
    private String description = null;
    private Map<String,Object> classifiers = null;

    @SuppressWarnings("unchecked")
    public DefaultMetadata(Map<String, Object> metadataMap) {
        setId((String) metadataMap.get("id"));
        setVersion(metadataMap.get("version"));
        setClassifiers((Map<String,Object>) metadataMap.get("classifiers"));
        setDescription((String) metadataMap.get("description"));
    }

    public String getId(){
        return this.id;
    }

    public Object getVersion() {
        return this.version;
    }

    public String getDescription() {
        return this.description;
    }

    public Map<String,Object> getClassifiers() {
        return this.classifiers;
    }

    public Object getClassifier(String classifierKey) {
        return getClassifiers().get(classifierKey);
    }

    private void setId(String id) {
        this.id = id;
    }

    private void setVersion(Object version) {
        this.version = version;
    }

    private void setDescription(String description) {
        this.description = description;
    }

    private void setClassifiers(Map<String,Object> classifiers) {
        this.classifiers = classifiers;
    }

}
