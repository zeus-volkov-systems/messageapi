package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IField;

/**
 * A collection is a primary dimension of a container. It contains a field set,
 * an identifier, and a map of classifiers. Classifiers can be used to group
 * collections together for use in protocols. Classifiers are key-value pairs,
 * where keys are strings, and values are either strings or lists of strings.
 * Collections also contain fields and optionally conditions. 
 * Fields in collections specify how requests factor their own field sets.
 * If conditions are specified on collections, they can be used to qualify records before
 * factoring the record into the collection.
 * @author Ryan Berkheimer
 */
public interface ICollection {

    /**
     * Returns the ID belonging to the Collection.
     */
    public String getId();

    /**
     * Returns the map of classifiers associated with the collection.
     * Classifiers are cross-collection, meaning a classifier
     * can be associated with multiple collections. Classifiers
     * have both a key and a value.
     */
    public Map<String,Object> getClassifiers();

    /**
     * Returns the field objects associated with this collection.
     */
    public List<IField> getFields();

    /**
     * Returns the classifier corresponding the the given classifer key.
     * This returns the classifier value.
     */
    public Object getClassifier(String classifierKey);

    /**
     * Returns a deep-copy of the collection
     */
    public ICollection getCopy();

    /**
     * Returns a list of condition ids associated with this collection
     */
    public List<String> getConditionIds();

}
