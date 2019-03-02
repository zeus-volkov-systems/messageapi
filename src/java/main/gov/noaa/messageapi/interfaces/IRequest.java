package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IResponse;

public interface IRequest {

    public IRecord createRecord();

    public IResponse process();

    public IRequest getCopy();
    public String getType();
    public IContainer getContainer();
    public ISchema getSchema();
    public IProtocol getProtocol();
    public List<IRecord> getRecords();

}
