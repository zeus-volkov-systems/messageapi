package gov.noaa.messageapi.transformations.reductions;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.transformations.BaseTransformation;


/**
 * @author Ryan Berkheimer
 */
public class ReduceTransformation extends BaseTransformation implements ITransformation {

    public ReduceTransformation(Map<String,Object> params) {
        super(params);
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        return transformationMap.get("reduce-list");
    }

}
