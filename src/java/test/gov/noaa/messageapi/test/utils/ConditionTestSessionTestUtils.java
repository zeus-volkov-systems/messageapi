package gov.noaa.messageapi.test.utils;

import java.util.Date;

import gov.noaa.messageapi.factories.SessionFactory;
import gov.noaa.messageapi.utils.general.PathUtils;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;


public class ConditionTestSessionTestUtils {

    private static final String sessionSpec =
        PathUtils.reconcileKeywords("{}/resources/test/sessions/condition-test.json");

    public static ISession getSession() throws Exception {
        return SessionFactory.create(sessionSpec);
    }

    public static IRequest getAddRequest() throws Exception {
        return getSession().createAddRequest();
    }

    public static void setTestRecordFields(IRecord record, Boolean b, Float f, Integer i, String s, Date d) {
        record.setField("boolean-required", b);
        record.setField("float-required", f);
        record.setField("integer-required", i);
        record.setField("string-required", s);
        record.setField("datetime-required", d);
    }

    public static void setTestRecordConditions(IRecord record, String s1, String s2) {
        record.setCondition("string-required-equals-1", s1);
        record.setCondition("string-required-equals-2", s2);
    }

    public static IRequest getTestAddRequest1() throws Exception {
        IRequest request = getAddRequest();
        IRecord r1 = request.createRecord();
        setTestRecordFields(r1, true, new Float(3.14159), 42, "test-string-value", new Date());
        setTestRecordConditions(r1, "test-string-value1", "test-string-value");
        System.out.println(r1.getField("string-required").getValue());
        System.out.println(r1.getCondition("string-required-equals-1").getValue());
        System.out.println(r1.getCondition("string-required-equals-2").getValue());
        return request;
    }
}
