package gov.noaa.messageapi.transformations.reductions;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.transformations.BaseTransformation;


/**
 * This class is currently stubbed - it does nothing but extract a reduce-list key from the transformation map
 * and return the records associated with this key.
 * @author Ryan Berkheimer
 */
public class ReduceTransformation extends BaseTransformation implements ITransformation {

    public ReduceTransformation(final Map<String, Object> params) {
        super(params);
    }

    public List<IRecord> process(final Map<String, List<IRecord>> transformationMap) {
        return transformationMap.get("reduce-list");
    }

}
