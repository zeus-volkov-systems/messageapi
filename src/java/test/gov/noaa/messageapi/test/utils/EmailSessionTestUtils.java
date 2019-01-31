package gov.noaa.messageapi.test.utils;

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.utils.general.PathUtils;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;


public class EmailSessionTestUtils {

    private static final String sessionSpec =
        PathUtils.reconcileKeywords("{}/resources/test/sessions/email-smtp-test.json");

    public static ISession getSession() throws Exception {
        return SessionFactory.create(sessionSpec);
    }

    public static IRequest getAddRequest() throws Exception {
        return getSession().createAddRequest();
    }

    public static void setTestRecordFields(IRecord record, String sender,
                                        String recipient, String subject, String body) {
        record.setField("sender", sender);
        record.setField("recipient", recipient);
        record.setField("subject", subject);
        record.setField("body", body);
    }

    public static void setTestRecordConditions(IRecord record, String senderequals) {
        record.setCondition("senderequals", senderequals);
    }

    public static IRequest getTestAddRequest1() throws Exception {
        IRequest request = getAddRequest();
        setTestRecordFields(request.createRecord(),"sender1", "recipient1", "subject1", "body1");
        setTestRecordFields(request.createRecord(),"sender2", "recipient2", "subject2", "body2");
        setTestRecordFields(request.createRecord(),"sender3", "recipient3", "subject3", "body3");
        setTestRecordFields(request.createRecord(), null, "recipient1", "subject1", "body1");
        return request;
    }

    public static IRequest getTestAddRequest2() throws Exception {
        IRequest request = getAddRequest();
        IRecord record1 = request.createRecord();
        IRecord record2 = request.createRecord();
        IRecord record3 = request.createRecord();
        IRecord record4 = request.createRecord();
        setTestRecordFields(record1,"sender1", "recipient1", "subject1", "body1");
        setTestRecordFields(record2,"sender2", "recipient2", "subject2", "body2");
        setTestRecordFields(record3,"sender3", "recipient3", "subject3", "body3");
        setTestRecordFields(record4, "sender4", "recipient1", "subject1", "body1");
        //we dont set a condition on record1, any sender is ok (success)
        setTestRecordConditions(record2, "sender2"); //record 2 must have a sender of sender2 (success)
        setTestRecordConditions(record3, "sender1"); //record 3 must have a sender of sender1 (fail)
        setTestRecordConditions(record4, "sender1"); //record 4 must have a sender of sender1 (fail)
        return request;
    }

    public static IRequest getTestAddRequest3() throws Exception {
        IRequest request = getAddRequest();
        IRecord record1 = request.createRecord();
        IRecord record2 = request.createRecord();
        IRecord record3 = request.createRecord();
        IRecord record4 = request.createRecord();
        setTestRecordFields(record1,"sender1", "recipient1", "subject1", "body1");
        setTestRecordFields(record2,"sender2", "recipient2", "subject2", "body2");
        setTestRecordFields(record3,"sender3", null, "subject3", "body3");
        setTestRecordFields(record4, null, "recipient1", "subject1", "body1");
        return request;
    }

}
