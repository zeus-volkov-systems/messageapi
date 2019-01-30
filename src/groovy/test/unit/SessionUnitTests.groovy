/**
 * Tests a variety of jobs using the test environment.
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class SessionUnitTests extends spock.lang.Specification {

    def "Test session bootstrapping."() {
        given: "session test spec."
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
        when: "We create a session"
            ISession session = SessionFactory.create(sessionSpec)
        then: "An ISession instance is created without error."
            session in gov.noaa.messageapi.interfaces.ISession
    }

    def "Test creating a session ADD request."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create an request"
            IRequest request = session.createAddRequest()
        then: "Add request is created and of the proper type"
            request.getType() == "add"
            request in gov.noaa.messageapi.interfaces.IRequest
    }

    def "Test creating two session requests, make sure they are different instances"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
        when: "We create two separate requests on the same session"
            IRequest r1 = session.createAddRequest()
            IRequest r2 = session.createAddRequest()
        then: "Then the two requests should be different instances."
            r1 != r2
    }

    def "Tests creating a new add record"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createAddRequest()
        when: "We create a record"
            IRecord record = request.createRecord()
        then: "The record is successfully created"
            record in gov.noaa.messageapi.interfaces.IRecord
    }

    def "Tests that the fields in the record are as expected."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createAddRequest()
            IRecord record = request.createRecord()
            def expectedFieldNames = ['id', 'key', 'record', 'filename', 'type', 'receipt_date', 'insert_date']
        when:
            def fieldNames = []
            record.getFields().each { field ->
                fieldNames.add(field.getName())
            }
        then:
            fieldNames == expectedFieldNames
    }

}
