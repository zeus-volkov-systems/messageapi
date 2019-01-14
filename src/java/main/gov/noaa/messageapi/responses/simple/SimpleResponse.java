package gov.noaa.messageapi.responses.simple;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.responses.BaseResponse;

public class SimpleResponse extends BaseResponse implements IResponse {

    public SimpleResponse(IRequest request) {
        super(request);
        setRejections(this.request.prepare());
        setRecords(this.request.process());
        setComplete(true);
    }

}
