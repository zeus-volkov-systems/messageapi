package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

public interface IResponse {

    public boolean isComplete();
    public List<IRejection> getRejections();
    public List<IRecord> getRecords();

}
