package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

/**
 * @author Ryan Berkheimer
 */
public interface IEndpoint {

    public IPacket process(IProtocolRecord record);
    public List<IField> getDefaultFields();
    public IRecord createRecord();

}
