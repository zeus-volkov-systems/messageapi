/**
 * Tests field utils public methods
 * @author Ryan Berkheimer
 */
import java.util.List;

import gov.noaa.messageapi.utils.schema.ConditionUtils;
import gov.noaa.messageapi.utils.schema.FieldUtils;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;

class FieldUtilsUnitTests extends spock.lang.Specification {

    def "Tests validation of a record against very simple field conditions."() {
        given: "A standard email session test setup with add request and the first record in that request"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest2()
            ISchema testSchema = testRequest.getSchema()
            IRecord testRecord = testRequest.getRecords().get(1)
            List<ICondition> testConditions = testRecord.getConditions()
        when: "We validate a record against its field conditions"
            boolean isValid = FieldUtils.validateConditions(testSchema, testRecord, testConditions)
        then: "The record should be valid (we expect conditions to be satisfied using this test data)"
            isValid == true
        }


}
