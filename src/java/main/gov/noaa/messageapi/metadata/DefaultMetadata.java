package gov.noaa.messageapi.metadata;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IMetadata;

/**
 * Metadata contains useful information regarding a specific plugin.
 * This can be used to provide context to a plugin, track schema changes
 * over time (like the Avro library), or otherwise automate/simplify plugin
 * use for library developers and users.
 */
public class DefaultMetadata implements IMetadata {

    private String id = null;
    private String version = null;
    private String description = null;
    private Map<String,Object> classifiers = null;

    @SuppressWarnings("unchecked")
    public DefaultMetadata(Map<String, Object> metadataMap) {
        setId((String) metadataMap.get("id"));
        setVersion((String) metadataMap.get("version"));
        setClassifiers((Map<String,Object>) metadataMap.get("classifiers"));
        setDescription((String) metadataMap.get("description"));
    }

    public String getId(){
        return this.id;
    }

    public String getVersion() {
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

    private void setVersion(String version) {
        this.version = version;
    }

    private void setDescription(String description) {
        this.description = description;
    }

    private void setClassifiers(Map<String,Object> classifiers) {
        this.classifiers = classifiers;
    }

}
