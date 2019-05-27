/**
 * Tests field operations
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;

class ConditionUnitTests extends spock.lang.Specification {


    def "Tests giving a value to a condition."() {
        given:
            def conditionValue = "testConditionValue"
            def sessionSpec = this.getClass().getResource('sessions/sqlite-jdbc-clisam.json').getPath()
            ISession session = SessionFactory.create(sessionSpec)
            IRequest request = session.createRequest()
            IRecord record = request.createRecord()
            ICondition condition = record.getCondition("1")
        when:
            condition.setValue(conditionValue)
        then:
            condition.getValue() == conditionValue
    }


}
