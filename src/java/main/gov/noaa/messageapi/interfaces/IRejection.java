package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;

/**
 * @author Ryan Berkheimer
 */
public interface IRejection {

    public IRecord getRecord();
    public IRejection getCopy();
    public List<String> getReasons();
    public void addReason(String reason);

}
