package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IContainerRecord;

public class ConditionEndpointTest implements IConnection {

    public ConditionEndpointTest(Map<String,Object> parameters) {
        System.out.println("Condition Endpoint Test!");
    }

    public void process(List<IContainerRecord> containerRecords) {
        System.out.println("Condition test processing: " + containerRecords);
    }

}
