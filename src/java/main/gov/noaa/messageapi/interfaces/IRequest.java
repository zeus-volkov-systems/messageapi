package gov.noaa.messageapi.interfaces;

import java.util.List;
import gov.noaa.messageapi.interfaces.IRecord;

public interface IRequest {

    public IRecord createRecord();

    public List<IRejection> prepare();
    public List<IRecord> process();

    public IRequest getCopy();
    public String getType();
    public IContainer getContainer();
    public ISchema getSchema();
    public IProtocol getProtocol();
    public List<IRecord> getRecords();

}
