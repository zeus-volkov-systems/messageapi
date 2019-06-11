/**
 * Tests session operations
 * @author Ryan Berkheimer
 */

 import gov.noaa.messageapi.interfaces.ISession;
 import gov.noaa.messageapi.interfaces.IRequest;
 import gov.noaa.messageapi.interfaces.IRecord;
 import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.sessions.DefaultSession;
class SessionUnitTests extends spock.lang.Specification {

    def "Test session creation from a json spec using factory."() {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = SessionFactory.create(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }

    def "Test default session creation from a json spec without using a factory." () {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = new DefaultSession(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }

    def "Test consumer session creation from a json spec without using a factory." () {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = new DefaultSession(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }
}
