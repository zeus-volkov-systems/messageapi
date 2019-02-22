package gov.noaa.messageapi.test.endpoints;

import java.util.List;
import java.util.Map;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.records.protocol.ProtocolRecord;

public class EmailEndpointTest implements IEndpoint {

    public EmailEndpointTest(Map<String,Object> parameters) {}

    public IProtocolRecord process(List<IContainerRecord> containerRecords) {
        return new ProtocolRecord();
    }

}
