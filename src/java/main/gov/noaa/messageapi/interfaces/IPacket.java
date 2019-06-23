package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

/**
 * IPackets are simple wrapper containers that hold together
 * a list of records and a list of rejections, and provide
 * methods for setting, retrieving, and adding to these
 * contained collections. IPackets are the return type of
 * Endpoints.
 * @author Ryan Berkheimer
 */
public interface IPacket {

    /**
     * Sets the records for the IPacket to the passed list of Records.
     * This replaces anything that was there before.
     */
    public void setRecords(List<IRecord> records);

    /**
     * Adds a record to the existing list of records in the IPacket.
     */
    public void addRecord(IRecord record);

    /**
     * Adds all the passed records to the existing list of records in the IPacket.
     */
    public void addRecords(List<IRecord> records);

    /**
     * Returns a list of all current records held by the IPacket.
     */
    public List<IRecord> getRecords();

    /**
     * Sets the rejections for the IPacket to the passed list of Rejections.
     * This replaces anything that was there before.
     */
    public void setRejections(List<IRejection> rejections);

    /**
     * Adds the given rejection to the existing list of IPacket rejections.
     */
    public void addRejection(IRejection rejection);

    /**
     * Adds all given rejections to the existing list of IPacket rejections.
     */
    public void addRejections(List<IRejection> rejections);

    /**
     * Returns a list of all current rejections held by the IPacket.
     */
    public List<IRejection> getRejections();

}
