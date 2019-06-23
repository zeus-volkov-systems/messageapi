package gov.noaa.messageapi.interfaces;

import java.util.Map;

/**
 * Metadata objects hold information related to
 * the parts of some dimension of a Session.
 * Protocols, Containers, and Schemas all have
 * metadata associated with them. Metadata can be used
 * to track or version these things as they might change.
 * @author Ryan Berkheimer
 */
public interface IMetadata {

    /**
     * Returns the ID of the given Session component.
     * This ID should be unique in the context of a
     * user's system in which multiple MessageAPI configurations
     * are used.
     */
    public String getId();

    /**
     * Returns the version of the component with the given ID.
     * The version can be used to note changes in things like,
     * for example, a schema field set.
     */
    public Object getVersion();

    /**
     * A user friendly description of the component. Should
     * provide some insight into how to use the component or
     * what its purpose is.
     */
    public String getDescription();

    /**
     * A map of arbitrary classifiers that might provide some
     * use in storage, retrieval, automation, or documentation.
     */
    public Map<String,Object> getClassifiers();

    /**
     * Returns a classifier map value for the given classifier key.
     */
    public Object getClassifier(String classifierKey);

}
