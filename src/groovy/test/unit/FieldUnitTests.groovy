/**
 * Tests field operations
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class FieldUnitTests extends spock.lang.Specification {

    def "Tests that fields in a record are named as expected and in the proper order."() {
        given:
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createAddRequest()
            IRecord record = request.createRecord()
            
            def expectedFieldNames = ['id', 'key', 'record', 'filename', 'type', 'receipt_date', 'insert_date']
        when:
            def fieldNames = []
            record.getFields().each { field -> fieldNames.add(field.getName()) }
        then:
            fieldNames == expectedFieldNames
    }

}
