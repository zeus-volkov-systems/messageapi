package gov.noaa.messageapi.transformations;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

public class ReduceTransformation implements ITransformation {

    public ReduceTransformation(List<String> fields, Map<String,Object> params) {
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        return transformationMap.get("test");
    }

}