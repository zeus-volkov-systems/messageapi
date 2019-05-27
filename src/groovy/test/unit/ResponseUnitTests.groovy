/**
 * Tests request operations
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.test.utils.ConditionTestSessionTestUtils;

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

class ResponseUnitTests extends spock.lang.Specification {


def "Tests the gathering of a reponse submission of a prepared request through a persistent session."() {
    given: "A standard condition test request"
        ISession session = ConditionTestSessionTestUtils.getSession();
        IRequest testRequest = ConditionTestSessionTestUtils.getTestAddRequest1()
    when: "We submit the test session and wait for completion"
        IResponse response = testRequest.submit()
        while (!response.getComplete()) {}
    then: "We should have no rejections"
        response.getRejections().size() == 0
        response.getRecords().size() == 6
    }

}
