/**
 * Tests request operations
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;
import gov.noaa.messageapi.test.utils.ConditionTestSessionTestUtils;

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class RequestUnitTests extends spock.lang.Specification {

    def "Test creating a default request."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create an add request"
            IRequest request = session.createRequest()
        then: "Add request is created and of the proper type"
            request.getType() == "default"
            request in gov.noaa.messageapi.interfaces.IRequest
    }

    def "Test creating two session add requests, make sure they are different instances"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create two separate requests on the same session"
            IRequest r1 = session.createRequest()
            IRequest r2 = session.createRequest()
        then: "Then the two requests should be different instances."
            r1 != r2
    }

    def "Test preparation of an add request and generation of schema rejections."() {
        given: "A standard email session test setup with add request and the first record in that request"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest5()
        when: "We call prepare on the test request"
            IResponse response = testRequest.submit()
            while (!response.getComplete()) {}
            List<IRejection> rejections = response.getRejections()
        then: "We should have the proper number of rejections due to the overall running process"
            rejections.size() == 2
            IRejection rej1 = rejections.get(0)
            IRejection rej2 = rejections.get(1)
            rej1.getReasons() == ["Required field body was missing a value."]
            rej1.getRecord().getField("sender").getValue() == "sender2"
            rej2.getReasons() == ["The record fields were invalidated against specified conditions."]
            rej2.getRecord().getField("sender").getValue() == "sender1"
        }

    def "Test add request preparation and processing with nested conditions."() {
        given: "A standard condition session test setup with add request and the first record in that request"
            IRequest testRequest = ConditionTestSessionTestUtils.getTestAddRequest1()
        when: "We submit the request"
            IResponse response = testRequest.submit()
            while (!response.getComplete()) {}
        then: "We should have no rejections"
            response.getRejections().size() == 0
        }

}
