package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

public interface IResponse {

    public boolean getComplete();
    public IRequest getRequest();
    public List<IRejection> getRejections();
    public List<IRecord> getRecords();

    public void setRecords(List<IRecord> records);
    public void setRejections(List<IRejection> rejections);
    public void setComplete(boolean isComplete);


}
