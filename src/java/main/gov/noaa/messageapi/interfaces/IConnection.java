package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainerRecord;

public interface IConnection {

    public void process(List<IContainerRecord> containerRecords);

}
