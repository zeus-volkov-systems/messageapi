package gov.noaa.messageapi.rejections.simple;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.rejections.BaseRejection;

public class SimpleRejection extends BaseRejection implements IRejection {

    public SimpleRejection(IRecord record) {
        super(record);
    }

    public SimpleRejection(IRecord record, String reason) {
        super(record);
        addReason(reason);
    }

    public SimpleRejection(IRecord record, List<String> reasons) {
        super(record, reasons);
    }

    public SimpleRejection(IRejection rejection) {
        super(rejection);
    }

    public SimpleRejection getCopy() {
        return new SimpleRejection(this);
    }


}
