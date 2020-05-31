package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

/**
 * @author Ryan Berkheimer
 */
public interface ITransformation {

    /**
     * The process method takes in a map of string and record mappings and is
     * the main runtime method for the transformation. These mapping
     * definitions are contained in the parameter spec. Note that transformations
     * are immutable assuming that a getCopy method is provided to any
     * custom user types, and this means that individual records may be manipulated
     * as desired and returned as needed in the transformation.
     */
    public List<IRecord> process(Map<String,List<IRecord>> transformationMap);

    /**
     * Returns the constructor map attached to the transformation. The constructor map
     * can be used to retrieve constructor parameters. Note that thread safety
     * cannot be guaranteed if these parameters are used for anything other than read only.
     */
    public Map<String, Object> getConstructor();

}
