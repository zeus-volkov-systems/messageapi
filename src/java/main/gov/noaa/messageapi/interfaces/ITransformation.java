package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;

public interface ITransformation {

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap);

}
