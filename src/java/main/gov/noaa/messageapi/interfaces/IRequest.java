package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;

/**
 * @author Ryan Berkheimer
 */
public interface IRequest {

    public IRecord createRecord();
    public IRequest getCopy();
    public String getType();
    public IContainer getContainer();
    public ISchema getSchema();
    public IProtocol getProtocol();
    public List<IRecord> getRecords();
    public IRecord getRequestRecord();
    public void setCondition(String id, Object value);

}
