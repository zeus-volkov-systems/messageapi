package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IEndpoint {

    public IProtocolRecord process(List<IContainerRecord> containerRecords);

}
