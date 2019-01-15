/**
 * Tests a variety of jobs using the test environment.
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;

class SessionUnitTests extends spock.lang.Specification {

    def "Test session bootstrapping."() {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = SessionFactory.create(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }

    def "Test add request creation."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create an request"
            IRequest request = session.createAddRequest()
        then: "Add request is created and of the proper type"
            request.getType() == "add"
            request in gov.noaa.messageapi.interfaces.IRequest
    }

}
