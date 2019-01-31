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

    public static IRequest getTestRequest1() throws Exception {
        IRequest request = getAddRequest();
        setTestRecordFields(request.createRecord(),"sender1", "recipient1", "subject1", "body1");
        setTestRecordFields(request.createRecord(),"sender2", "recipient2", "subject2", "body2");
        setTestRecordFields(request.createRecord(),"sender3", "recipient3", "subject3", "body3");
        setTestRecordFields(request.createRecord(), null, "recipient1", "subject1", "body1");
        return request;
    }
}
