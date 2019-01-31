/**
 * Tests field operations
 */
import java.util.List;

import gov.noaa.messageapi.utils.request.RejectionUtils;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRejection;

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;

class RejectionUtilsUnitTests extends spock.lang.Specification {


    def "Tests rejection of a missing required record in a set with proper return message."() {
        given: "A standard email session test setup with add request"
            IRequest testRequest = EmailSessionTestUtils.getTestRequest1()
        when: "we pass the request through the rejection utils method to test rejecting missing required fields"
            List<IRejection> rejections = RejectionUtils.getRequiredFieldRejections(testRequest.getRecords());
        then: "we should reject 1 record due to a missing value on a required field, and the message should be correct"
            rejections.size() == 1
            rejections.get(0).getReasons().size() == 1
            rejections.get(0).getReasons().get(0) == "Required field sender was missing a value."
    }


}
