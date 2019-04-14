package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IField;

/**
 * A collection is a primary dimension of a container. It contains a field set,
 * an identifier, and a map of classifiers. Classifiers can be used to group
 * collections together for use in protocols. Classifiers are key-value pairs,
 * where keys are strings, and values are either strings or lists of strings.
 */
public interface ICollection {

    public String getId();
    public Map<String,Object> getClassifiers();
    public List<IField> getFields();
    public Object getClassifier(String classifierKey);
    public ICollection getCopy();

}
