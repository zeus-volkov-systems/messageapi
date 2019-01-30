/**
 * Tests session operations
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class SessionUnitTests extends spock.lang.Specification {

    def "Test session creation from a json spec."() {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = SessionFactory.create(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }
}
