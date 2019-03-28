package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.ISubmission;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IConnection {

    public String getId();
    public List<String> getBins();
    public List<String> getClassifiers();
    public List<String> getClassifers(String classifierKey);
    public ISubmission process(IProtocolRecord record);

}
