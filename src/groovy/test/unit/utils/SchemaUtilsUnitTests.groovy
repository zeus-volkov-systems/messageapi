/**
 * Tests schema utils public methods
 * @author Ryan Berkheimer
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


    def "Tests filtering non-valued fields from records in a record set."() {
        given: "a request with a set of records"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest3()
            List<IRecord> testRecords = testRequest.getRecords()
        when: "we remove fields from records where the fields have not been assigned values"
            List<IRecord> updatedTestRecords = SchemaUtils.filterNonValuedFields(testRecords)
        then: "All records should still exist, but their field sets should be adjusted based on rejected fields"
            updatedTestRecords.size() == 4
            updatedTestRecords.get(0).getFields().size() == 4
            updatedTestRecords.get(1).getFields().size() == 4
            updatedTestRecords.get(2).getFields().size() == 3
            updatedTestRecords.get(3).getFields().size() == 3
        }

    def "Tests filtering non-valued conditions from records in a record set."() {
        given: "a request with a set of records"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest2()
            List<IRecord> testRecords = testRequest.getRecords()
        when: "we remove conditions from records where the conditions have not been assigned values"
            List<IRecord> updatedTestRecords = SchemaUtils.filterNonValuedConditions(testRecords)
        then: "All records should still exist, but their condition sets should be adjusted based on rejected fields"
            updatedTestRecords.size() == 4
            updatedTestRecords.get(0).getConditions().size() == 0
            updatedTestRecords.get(1).getConditions().size() == 1
            updatedTestRecords.get(2).getConditions().size() == 1
            updatedTestRecords.get(3).getConditions().size() == 1
        }

    def "Tests filtering non-valued conditions from records in a record set."() {
        given: "a request with a set of records"
            IRequest testRequest = EmailSessionTestUtils.getTestAddRequest4()
            List<IRecord> testRecords = testRequest.getRecords()
        when: "we remove fields from records where the fields have not been assigned values and then remove associated conditions that reference those fields"
            List<IRecord> updatedTestRecords = SchemaUtils.filterFieldlessConditions(SchemaUtils.filterNonValuedFields(testRecords))
        then: "All records should still exist, but their condition sets should be adjusted based on rejected fields"
            updatedTestRecords.size() == 4
            updatedTestRecords.get(0).getConditions().size() == 1
            updatedTestRecords.get(1).getConditions().size() == 0
            updatedTestRecords.get(2).getConditions().size() == 1
            updatedTestRecords.get(3).getConditions().size() == 1
        }



}
