/**
 * Tests field operations
 */
import java.util.List;

import gov.noaa.messageapi.utils.schema.ConditionUtils;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;

class ConditionUtilsUnitTests extends spock.lang.Specification {


    def "Tests assembly of top level conditions on a simple/flat request condition set."() {
        given: "A standard email session test setup with add request and the first record in that request"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest2()
            IRecord record1 = testRequest.getRecords().get(0)
        when: "we look at the top level conditions"
            List<ICondition> conditions = ConditionUtils.getTopLevelConditions(record1);
        then: "we should get one top level condition"
            conditions.size() == 1
            conditions.get(0).getId() == "senderequals"
    }


}
