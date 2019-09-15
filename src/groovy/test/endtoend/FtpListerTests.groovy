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

class FtpListerTests extends spock.lang.Specification {

def "Tests submission of a request containing a record that contains a directory field to retrieve contents of.This tests basic functionality of the FtpLister endpoint."() {
    given: "A session created based on a ftp-lister manifest."
        ISession session = new DefaultSession("{}/resources/test/ftp-lister/manifest.json")
        IRequest request = session.createRequest();
        IRecord record = request.createRecord();
        record.setField("directory", "pub/download/hidden");
    when: "We submit the request with a single record containing a single field (directory) that has a directory to process"
        IResponse response = request.submit();
        while (!response.isComplete()) {}
        println "Getting a response..."
        response.getRecords().each { r ->
            println r.getField("name").getValue()
            println r.getField("server").getValue()
            println r.getField("path").getValue()
            println r.getField("size").getValue()
            println r.getField("type").getValue()
            println r.getField("modified").getValue()
        }
    then: "We should have no rejections."
        response.getRejections().size() == 0
        //response.getRecords().size() == 6
    }

}
