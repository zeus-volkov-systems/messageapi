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
    public DefaultMetadata(final Map<String, Object> metadataMap) {
        try {
            if (metadataMap.containsKey("id")) {
                this.setId((String) metadataMap.get("id"));
            }
            if (metadataMap.containsKey("version")) {
                this.setVersion(metadataMap.get("version"));
            }
            if (metadataMap.containsKey("classifiers")) {
                this.setClassifiers((Map<String, Object>) metadataMap.get("classifiers"));
            }
            if (metadataMap.containsKey("description")) {
                this.setDescription((String) metadataMap.get("description"));
            }
        } catch (final Exception e) {
        }
    }

    public String getId() {
        return this.id;
    }

    public Object getVersion() {
        return this.version;
    }

    public String getDescription() {
        return this.description;
    }

    public Map<String, Object> getClassifiers() {
        return this.classifiers;
    }

    public Object getClassifier(final String classifierKey) {
        return getClassifiers().get(classifierKey);
    }

    private void setId(final String id) {
        this.id = id;
    }

    private void setVersion(final Object version) {
        this.version = version;
    }

    private void setDescription(final String description) {
        this.description = description;
    }

    private void setClassifiers(final Map<String, Object> classifiers) {
        this.classifiers = classifiers;
    }

}
