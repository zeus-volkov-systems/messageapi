package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRecord;

/**
 * @author Ryan Berkheimer
 */
public interface IRequest {

    public IRecord createRecord();
    public IRequest getCopy();
    public IRequest getCopy(List<String> copyComponents);
    public String getType();
    public IContainer getContainer();
    public ISchema getSchema();
    public IProtocol getProtocol();
    public List<IRecord> getRecords();
    public IRecord getRequestRecord();
    public void setCondition(String id, Object value);
    public void setRecords(List<IRecord> records);
    public IResponse submit();

}
