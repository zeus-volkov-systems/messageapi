package gov.noaa.messageapi.rejections;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

/**
 * @author Ryan Berkheimer
 */
public class DefaultRejection extends BaseRejection implements IRejection {

    public DefaultRejection(final IRecord record) {
        super(record);
    }

    public DefaultRejection(final IRecord record, final String reason) {
        super(record);
        addReason(reason);
    }

    public DefaultRejection(final IRecord record, final List<String> reasons) {
        super(record, reasons);
    }

    public DefaultRejection(final IRejection rejection) {
        super(rejection);
    }

    public DefaultRejection getCopy() {
        return new DefaultRejection(this);
    }


}
