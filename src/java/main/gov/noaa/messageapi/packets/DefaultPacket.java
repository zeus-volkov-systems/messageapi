package gov.noaa.messageapi.packets;

import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

/**
 * A packet is a simple collection of a record list and a rejection list with
 * facilities to add to, replace, and retrieve those lists.
 * @author Ryan Berkheimer
 */
public class DefaultPacket implements IPacket {

    public List<IRecord> records = null;
    public List<IRejection> rejections = null;

    public DefaultPacket() {
        this.records = new ArrayList<IRecord>();
        this.rejections = new ArrayList<IRejection>();
    }

    public DefaultPacket(final List<IRecord> records, final List<IRejection> rejections) {
        this.records = records;
        this.rejections = rejections;
    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public List<IRejection> getRejections() {
        return this.rejections;
    }

    public void setRecords(final List<IRecord> records) {
        this.records = records;
    }

    public void setRejections(final List<IRejection> rejections) {
        this.rejections = rejections;
    }

    public void addRecord(final IRecord record) {
        this.records.add(record);
    }

    public void addRejection(final IRejection rejection) {
        this.rejections.add(rejection);
    }

    public void addRecords(final List<IRecord> records) {
        this.records.addAll(records);
    }

    public void addRejections(final List<IRejection> rejections) {
        this.rejections.addAll(rejections);
    }


}
