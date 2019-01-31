/**
 * Tests schema utils public methods
 */
import java.util.List;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

import gov.noaa.messageapi.utils.request.SchemaUtils;
import gov.noaa.messageapi.utils.request.RejectionUtils;

import gov.noaa.messageapi.test.utils.EmailSessionTestUtils;

class SchemaUtilsUnitTests extends spock.lang.Specification {

    def "Tests removing rejected records from a record set."() {
        given: "a request with a set of records and known rejections"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest3()
            List<IRecord> testRecords = testRequest.getRecords()
            List<IRejection> testRejections = RejectionUtils.getRequiredFieldRejections(testRecords)
        when: "we attempt to remove the rejections from the list of existing records"
            List<IRecord> updatedTestRecords = SchemaUtils.filterRejections(testRecords, testRejections)
        then: "There should be two contained records in the resulting set and both should be what is expected"
            updatedTestRecords.size() == 2
            updatedTestRecords.get(0).getField("sender").getValue() == "sender1"
            updatedTestRecords.get(1).getField("sender").getValue() == "sender2"
        }


}
