package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IEndpoint {

    public IPacket process(IProtocolRecord record);

}
