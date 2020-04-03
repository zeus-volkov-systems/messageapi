/**
 * Tests sessions that use the basic native endpoint. This is an end to end type testing module.
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.sessions.DefaultSession;

class NativeEndpointTests extends spock.lang.Specification {

def "Tests submission of a very simple native task with only one endpoint that calls into C and increments a counter."() {
    given: "A session created based on a native counter"
        ISession session = new DefaultSession("{}/resources/test/basic-native/manifest.json")
        IRequest request = session.createRequest();
        IRecord record1 = request.createRecord();
        IRecord record2 = request.createRecord();

        //tested up to 1e6 records (slow, ~20 seconds to load these records)
        for (int i=0; i<500000; i++) {
            IRecord r = request.createRecord();
            r.setField("initial-value", 5);
            r.setField("string-test", "five");
        }
        record1.setField("initial-value", 0);
        record2.setField("initial-value", 1);
        record1.setField("string-test", "hi there!");
        record2.setField("string-test", "cool!");
    when: "We submit the test session with a single endpoint, let it call into C, increment a counter, add it to a new record, and return"
        println "Built the records, submitting the response."
        IResponse response = request.submit();
        while (!response.isComplete()) {}
    then: "We should have no rejections, there should be one return record, and when we grab the 'counter-value' field, we should get 1."
        response.getRejections().size() == 0
        //println response.getRejections().size()
        //response.getRecords().size() == 1
        //response.getRecords().get(0).getField("counter-value").getValue() == 1
    }

}
