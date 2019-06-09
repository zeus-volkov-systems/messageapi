package gov.noaa.messageapi.test.factories.transformations;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.ITransformation;
import gov.noaa.messageapi.interfaces.ITransformationFactory;
import gov.noaa.messageapi.test.transformations.FixRelativePathsTransformation;

/**
 * @author Ryan Berkheimer
 */
public class FileReaderFactory implements ITransformationFactory {

    /**
     * Returns an operator based on a data type name as a string.
     * @param  type The type of operator to return
     * @return      A new operator based on the specified type
     */
    public ITransformation getTransformation(String type, List<String> fields, Map<String,Object> params) {
        switch (type) {
            case "fix-relative-paths":
                return new FixRelativePathsTransformation(fields, params);
            default:
                return null;
        }
    }

}
