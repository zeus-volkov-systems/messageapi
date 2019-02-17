package gov.noaa.messageapi.rejections;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.rejections.BaseRejection;

public class DefaultRejection extends BaseRejection implements IRejection {

    public DefaultRejection(IRecord record) {
        super(record);
    }

    public DefaultRejection(IRecord record, String reason) {
        super(record);
        addReason(reason);
    }

    public DefaultRejection(IRecord record, List<String> reasons) {
        super(record, reasons);
    }

    public DefaultRejection(IRejection rejection) {
        super(rejection);
    }

    public DefaultRejection getCopy() {
        return new DefaultRejection(this);
    }


}
