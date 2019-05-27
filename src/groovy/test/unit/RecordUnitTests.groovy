/**
 * Tests record operations
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class RecordUnitTests extends spock.lang.Specification {


    def "Tests creating a new record"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
        when: "We create a record on a request"
            IRecord record = request.createRecord()
        then: "The record is successfully created"
            record in gov.noaa.messageapi.interfaces.IRecord
    }

    def "Verifies that two records created on the same request are unique"() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
        when: "We create two records on the same request"
            IRecord r1 = request.createRecord()
            IRecord r2 = request.createRecord()
        then: "Both records are unique"
            r1 != r2
    }


    def "Tests that the fields in the record are as expected."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
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
