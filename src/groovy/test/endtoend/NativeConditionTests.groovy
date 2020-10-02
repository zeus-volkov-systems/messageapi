/**
 * Tests sessions that use the native transformation. This is an end to end type testing module.
 * @author Ryan Berkheimer
 */

import java.util.List

import gov.noaa.messageapi.interfaces.ISession
import gov.noaa.messageapi.interfaces.IRequest
import gov.noaa.messageapi.interfaces.IResponse
import gov.noaa.messageapi.interfaces.IRejection
import gov.noaa.messageapi.interfaces.IRecord
import gov.noaa.messageapi.interfaces.IField

import gov.noaa.messageapi.utils.general.PathUtils
import gov.noaa.messageapi.sessions.StandardSession

class NativeConditionTests extends spock.lang.Specification {

def "Tests submission of a simple native condition comparing integer fields using a Standard Session."() {
    given: 'A standard session based condition test request'
        String parameterPath = PathUtils.reconcileKeywords('{}/resources/test/native-condition/parameters.json')
        println parameterPath
        ISession session = new StandardSession(parameterPath)
        IRequest request = session.createRequest()
        IRecord record = request.createRecord()
        //String filePath = '{}/resources/test/inputs/file-reader/proc_sm_gtsnp_data_ftp_CF6_cf6_20190506.txt'
        record.setField('int-field', 10)
        //println record.getField('file-path').getValue()
    when: 'We submit the test session and wait for completion'
        println 'submitting native condition test'
        IResponse response = request.submit()
        println 'submitted native condition test'
        while (!response.isComplete()) {}
        println 'native condition response is complete'
    then: 'We should have no rejections.'
        //println response.getRecords().get(0).getField("value").getValue()
        response.getRejections().size() == 0
        //println 'Size of return records: ' + response.getRecords().size()
        //response.getRecords().size() == 79794
    }

}
