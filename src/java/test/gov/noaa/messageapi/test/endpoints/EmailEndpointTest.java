package gov.noaa.messageapi.test.endpoints;

import java.util.List;
import java.util.Map;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IContainerRecord;

public class EmailEndpointTest implements IConnection {

    public EmailEndpointTest(Map<String,Object> parameters) {
        System.out.println("Email Endpoint Test!!!");
    }

    public void process(List<IContainerRecord> containerRecords) {
        System.out.println("Email endpoint test processing: " + containerRecords);
    }

}
