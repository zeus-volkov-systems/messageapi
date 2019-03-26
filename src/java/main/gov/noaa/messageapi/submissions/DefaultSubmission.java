package gov.noaa.messageapi.submissions;

import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.ISubmission;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

/**
 * A submission is a simple collection of a record list and a rejection list with
 * facilities to add to, replace, and retrieve those lists.
 */
public class DefaultSubmission implements ISubmission {

    public List<IRecord> records = null;
    public List<IRejection> rejections = null;

    public DefaultSubmission() {
        this.records = new ArrayList<IRecord>();
        this.rejections = new ArrayList<IRejection>();
    }

    public DefaultSubmission(List<IRecord> records, List<IRejection> rejections) {
        this.records = records;
        this.rejections = rejections;
    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public List<IRejection> getRejections() {
        return this.rejections;
    }

    public void setRecords(List<IRecord> records) {
        this.records = records;
    }

    public void setRejections(List<IRejection> rejections) {
        this.rejections = rejections;
    }

    public void addRecord(IRecord record) {
        this.records.add(record);
    }

    public void addRejection(IRejection rejection) {
        this.rejections.add(rejection);
    }

    public void addRecords(List<IRecord> records) {
        List<IRecord> newRecords = new ArrayList<IRecord>();
        newRecords.addAll(this.records);
        newRecords.addAll(records);
        this.records = newRecords;
    }

    public void addRejections(List<IRejection> rejections) {
        List<IRejection> newRejections = new ArrayList<IRejection>();
        newRejections.addAll(this.rejections);
        newRejections.addAll(rejections);
    }


}
