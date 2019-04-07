package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.ISubmission;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IConnection {

    public String getId();
    public List<String> getBins();
    public  Map<String,List<Object>> getClassifiers();
    public List<Object> getClassifers(String classifierKey);
    public ISubmission process(IProtocolRecord record);

}
