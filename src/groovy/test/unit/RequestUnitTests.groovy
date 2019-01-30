/**
 * Tests request operations
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class RequestUnitTests extends spock.lang.Specification {

    def "Test creating an add request."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create an add request"
            IRequest request = session.createAddRequest()
        then: "Add request is created and of the proper type"
            request.getType() == "add"
            request in gov.noaa.messageapi.interfaces.IRequest
    }

    def "Test creating two session add requests, make sure they are different instances"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create two separate requests on the same session"
            IRequest r1 = session.createAddRequest()
            IRequest r2 = session.createAddRequest()
        then: "Then the two requests should be different instances."
            r1 != r2
    }

}
