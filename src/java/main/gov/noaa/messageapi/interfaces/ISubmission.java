package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

public interface ISubmission {

    public void setRecords(List<IRecord> records);
    public void addRecord(IRecord record);
    public void addRecords(List<IRecord> records);
    public List<IRecord> getRecords();

    public void setRejections(List<IRejection> rejections);
    public void addRejection(IRejection rejection);
    public void addRejections(List<IRejection> rejections);
    public List<IRejection> getRejections();

}
