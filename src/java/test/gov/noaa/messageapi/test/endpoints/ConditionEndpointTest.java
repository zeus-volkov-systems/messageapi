package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.records.protocol.ProtocolRecord;

public class ConditionEndpointTest implements IEndpoint {

    public ConditionEndpointTest(Map<String,Object> parameters) {}

    public IProtocolRecord process(List<IContainerRecord> containerRecords) {
        return new ProtocolRecord();
    }

}
