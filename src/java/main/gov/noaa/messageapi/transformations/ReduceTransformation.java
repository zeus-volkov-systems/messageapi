package gov.noaa.messageapi.transformations;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

public class ReduceTransformation implements ITransformation {

    public ReduceTransformation(List<String> fields, Map<String,Object> params) {
        System.out.println("Reduce Transformation CTR");
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        System.out.println("we be reducin this thing...");
        System.out.println(transformationMap);
        return transformationMap.get("reduce-list");
    }

}
