/**
 * Tests field operations
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.sessions.SequentialSession;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class FieldUnitTests extends spock.lang.Specification {

    def "Tests that fields in a record are named as expected and in the proper order."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = new SequentialSession(sessionSpec)
            IRequest request = session.createRequest()
            IRecord record = request.createRecord()

            def expectedFieldNames = ['id', 'key', 'record', 'filename', 'type', 'receipt_date', 'insert_date']
        when:
            def fieldNames = []
            record.getFields().each { field -> fieldNames.add(field.getName()) }
        then:
            fieldNames == expectedFieldNames
    }

    def "Tests updating a non-required field value."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
            IRecord record = request.createRecord()
            IField field = record.getField("id")
        when:
            field.setValue(5)
        then:
            field.getValue() == 5
            field.isValid() == true
    }

    def "Tests updating a required field value."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
            IRecord record = request.createRecord()
            IField field = record.getField("key")
        when:
            field.setValue("test_key")
        then:
            field.getValue() == "test_key"
            field.isValid() == true
    }


}
