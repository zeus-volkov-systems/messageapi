package gov.noaa.messageapi.rejections;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

/**
 * @author Ryan Berkheimer
 */
public class BaseRejection {

    private List<String> reasons = null;
    private IRecord record = null;

    public BaseRejection(IRecord record) {
        setRecord(record);
        initializeReasons();
    }

    public BaseRejection(IRecord record, List<String> reasons) {
        setRecord(record);
        setReasons(reasons);
    }

    public BaseRejection(IRejection rejection) {
        setRecord(rejection.getRecord());
        setReasons(rejection.getReasons());
    }

    public IRecord getRecord() {
        return this.record;
    }

    public List<String> getReasons() {
        return this.reasons;
    }

    private void initializeReasons() {
        this.reasons = Collections.synchronizedList(new ArrayList<String>());
    }

    public void addReason(String reason) {
        this.reasons.add(reason);
    }

    private void setRecord(IRecord record) {
        this.record = record;
    }

    private void setReasons(List<String> reasons) {
        this.reasons = Collections.synchronizedList(new ArrayList<String>(reasons));
    }

}
