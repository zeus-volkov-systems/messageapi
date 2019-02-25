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
        return getSession().createRequest();
    }

    public static void setTestRecordFields(IRecord record, Boolean bool, Float f, Double d, Integer integer, String string, Date date) {
        record.setField("boolean-required", bool);
        record.setField("float-required", f);
        record.setField("double-required", d);
        record.setField("integer-required", integer);
        record.setField("string-required", string);
        record.setField("datetime-required", date);
    }

    public static void setTestRecordConditions(IRecord record, String s1, String s2, Integer i1) {
        record.setCondition("string-required-equals-1", s1);
        record.setCondition("string-required-equals-2", s2);
        record.setCondition("integer-required-less-than", i1);
    }

    public static IRequest getTestAddRequest1() throws Exception {
        IRequest request = getAddRequest();
        IRecord r1 = request.createRecord();
        setTestRecordFields(r1, true, new Float(3.14159), new Double(5.234232342), 42, "test-string-value", new Date());
        setTestRecordConditions(r1, "test-string-value1", "test-string-value", 50);
        return request;
    }
}
