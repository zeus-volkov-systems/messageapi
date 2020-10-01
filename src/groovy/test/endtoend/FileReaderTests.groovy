/**
 * Tests sessions that use the file reader. This is an end to end type testing module.
 * @author Ryan Berkheimer
 */

import gov.noaa.messageapi.interfaces.ISession
import gov.noaa.messageapi.interfaces.IRequest
import gov.noaa.messageapi.interfaces.IResponse
import gov.noaa.messageapi.interfaces.IRecord

import gov.noaa.messageapi.sessions.DefaultSession
import gov.noaa.messageapi.sessions.StandardSession

import gov.noaa.messageapi.utils.general.PathUtils

/**
This Spock test class demonstrates end to end behaviors for reading and validating reads of files.
It should hold file reader transformation and file reader endpoint, and things like that.
*/
class FileReaderTests extends spock.lang.Specification {

/*def "Tests submission of a full file reader task with 1 small input."() {
    given: "A standard condition test request"
        ISession session = new DefaultSession("{}/resources/test/file-reader/manifest.json")
        IRequest request = session.createRequest();
        IRecord record = request.createRecord();
        record.setField("file-path", "{}/resources/test/inputs/file-reader/simpletextfile");
    when: "We submit the test session and wait for completion"
        IResponse response = request.submit();
        while (!response.isComplete()) {}
    then: "We should have no rejections and there should be 7 records in the return set."
        response.getRejections().size() == 0
        response.getRecords().size() == 7
}*/

def "Tests submission of a full file reader task with 1 large input using a Default Session."() {
    given: 'A default session condition test request'
        ISession session = new DefaultSession('{}/resources/test/file-reader/manifest.json')
        IRequest request = session.createRequest()
        IRecord record = request.createRecord()
        record.setField('file-path', '{}/resources/test/inputs/file-reader/proc_sm_gtsnp_data_ftp_CF6_cf6_20190506.txt')
    when: 'We submit the test session and wait for completion'
        IResponse response = request.submit()
        while (!response.isComplete()) {}
    then: 'We should have no rejections and there should be 79794 records in the return set.'
        //println response.getRecords().get(0).getField("value").getValue()
        response.getRejections().size() == 0
        response.getRecords().size() == 79794
        println 'finished default session test!'
    }

def "Tests submission of a full file reader task with 1 large input using a Standard Session."() {
    given: 'A standard session based condition test request'
        String parameterPath = PathUtils.reconcileKeywords('{}/resources/test/file-reader/parameter_map_style.json')
        println parameterPath
        ISession session = new StandardSession(parameterPath)
        IRequest request = session.createRequest()
        IRecord record = request.createRecord()
        //String filePath = '{}/resources/test/inputs/file-reader/proc_sm_gtsnp_data_ftp_CF6_cf6_20190506.txt'
        String filePath = '/workspaces/messageapi/build/resources/test/inputs/file-reader/proc_sm_gtsnp_data_ftp_CF6_cf6_20190506.txt'
        record.setField('file-path', filePath)
        //println record.getField('file-path').getValue()
    when: 'We submit the test session and wait for completion'
        //println 'submitting standard session test'
        IResponse response = request.submit()
        //println 'submitted standard session test'
        while (!response.isComplete()) {}
        //println 'response is complete'
    then: 'We should have no rejections and there should be 79794 records in the return set.'
        //println response.getRecords().get(0).getField("value").getValue()
        response.getRejections().size() == 0
        //println 'Size of return records: ' + response.getRecords().size()
        response.getRecords().size() == 79794
    }


}
