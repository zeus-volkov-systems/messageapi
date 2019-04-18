package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.ITransformation;

public interface ITransformationFactory {

    public ITransformation getTransformation(String id, List<String> fields, Map<String,Object> params);

}
