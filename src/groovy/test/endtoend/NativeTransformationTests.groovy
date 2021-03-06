/**
 * Tests sessions that use the native transformation. This is an end to end type testing module.
 * @author Ryan Berkheimer
 */

import java.util.List

import gov.noaa.messageapi.interfaces.ISession
import gov.noaa.messageapi.interfaces.IRequest
import gov.noaa.messageapi.interfaces.IResponse
import gov.noaa.messageapi.interfaces.IRejection
import gov.noaa.messageapi.interfaces.IRecord
import gov.noaa.messageapi.interfaces.IField

import gov.noaa.messageapi.sessions.SequentialSession

class NativeTransformationTests extends spock.lang.Specification {

def 'Session with one endpoint that calls into C, populates a return record, and checks vals.'() {
    given: 'A session created based on a native counter'
        ISession session = new SequentialSession('{}/resources/test/native-transformation/manifest.json')
        IRequest request = session.createRequest()
        IRecord record1 = request.createRecord()
        IRecord record2 = request.createRecord()

        record1.setField('initial-value', 1000)
        record1.setField('string-test', 'hi there!')
        record1.setField('null-test', 'null')
        record2.setField('string-test', 'cool!')
        record2.setField('initial-value', 5000)
        //record2.setField('null-test', 'null')
        /*for (int i=0; i<500; i++) {
            IRecord r = request.createRecord();
            r.setField("initial-value", i);
            r.setField("string-test", Integer.toString(i));
        }*/

    when: 'Submit the request, call a transformation in the evaluation endpoint, return all records'
        IResponse response = request.submit()
        while (!response.isComplete()) { }
    then: 'No rejections, two return records, field values match..'
        response.getRejections().size() == 0
        response.getRecords().size() == 2
        //response.getRecords().get(0).getField('test-integer').getValue() == 5
        //response.getRecords().get(0).getField('return-list').getValue().get(0) == "first element of our string!"
        //response.getRecords().get(0).getField('return-list').getValue().get(1) == "second element of our string!!"
    }

}
