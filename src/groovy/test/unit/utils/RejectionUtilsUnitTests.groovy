/**
 * Tests rejection utils public methods
 */
import java.util.List;

import gov.noaa.messageapi.utils.request.RejectionUtils;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRejection;

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;

class RejectionUtilsUnitTests extends spock.lang.Specification {

    def "Tests rejection of a missing required record in a set with proper return message."() {
        given: "A standard email session test setup with add request"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest1()
        when: "we pass the request through the rejection utils method to test rejecting missing required fields"
            List<IRejection> rejections = RejectionUtils.getRequiredFieldRejections(testRequest.getRecords());
        then: "we should reject 1 record due to a missing value on a required field, and the message should be correct"
            rejections.size() == 1
            rejections.get(0).getReasons().size() == 1
            rejections.get(0).getReasons().get(0) == "Required field sender was missing a value."
    }

    def "Tests rejection of a string field in a record set which does not conform to the expected equals condition"() {
        given: "A standard email session test setup with add request and conditioned records"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest2()
        when: "we pass the request through the rejection utils method to test rejecting records based on fields that do not properly conform to conditions"
            List<IRejection> rejections = RejectionUtils.getFieldConditionRejections(testRequest.getSchema(), testRequest.getRecords())
        then: "we should reject 3 records due to bad conditions (out of 4 total records) and the message should be correct."
            rejections.size() == 3
    }


}
