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
        given:
            IRequest testRequest = EmailSessionTestUtils.getTestRequest1()
        when:
            List<IRejection> rejections = RejectionUtils.getRequiredFieldRejections(testRequest.getRecords());
        then:
            rejections.size() == 1
            rejections.get(0).getReasons().size() == 1
            rejections.get(0).getReasons().get(0) == "Required field sender was missing a value."
    }


}
