/**
 * Tests sessions that use the file reader. This is an end to end type testing module.
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.sessions.PublisherSession;

class FileReaderTests extends spock.lang.Specification {


def "Tests submission of a full file reader task with 1 small input."() {
    given: "A standard condition test request"
        ISession session = new PublisherSession("{}/resources/test/file-reader/manifest.json")
        IRequest request = session.createRequest();
        IRecord record = request.createRecord();
        record.setField("file-path", "{}/resources/test/inputs/file-reader/simpletextfile");
    when: "We submit the test session and wait for completion"
        IResponse response = request.submit();
        while (!response.getComplete()) {}
    then: "We should have no rejections and there should be 7 records in the return set."
        response.getRejections().size() == 0
        response.getRecords().size() == 7
    }


}