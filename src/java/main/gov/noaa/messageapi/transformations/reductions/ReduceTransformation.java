package gov.noaa.messageapi.transformations.reductions;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;


/**
 * @author Ryan Berkheimer
 */
public class ReduceTransformation implements ITransformation {

    public ReduceTransformation(List<String> fields, Map<String,Object> params) {
        System.out.println("Reduce Transformation constuctor");
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        System.out.println("Reduction processing");
        System.out.println(transformationMap);
        return transformationMap.get("reduce-list");
    }

}
