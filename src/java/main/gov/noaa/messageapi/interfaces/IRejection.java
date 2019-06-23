package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;

/**
 * The IRejection serves as a device for recording
 * what IRecords are rejected during processing,
 * either in filtering, factoring, transformation, or
 * endpoint operations, or otherwise. Every rejection
 * holds a reference to the record that was rejected and
 * one or more reasons for rejection, recorded as Strings.
 * @author Ryan Berkheimer
 */
public interface IRejection {

    /**
     * Returns the record that the rejection references.
     */
    public IRecord getRecord();

    /**
     * Returns a deep-copy of the rejection in the current state.
     */
    public IRejection getCopy();

    /**
     * Returns a list of reasons (as strings) for the rejection.
     * These reasons could be anything and can be used for different purposes,
     * i.e., automation of retry, re-routing, etc.
     */
    public List<String> getReasons();

    /**
     * Adds a reason for rejection to the current list of reasons.
     */
    public void addReason(String reason);

}
