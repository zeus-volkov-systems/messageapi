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
            IRequest request = session.createAddRequest()
        then: "A session instance is created without error."
            request.getType() == "add"
    }

}
