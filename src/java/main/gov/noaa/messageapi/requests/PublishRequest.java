package gov.noaa.messageapi.requests;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;

import gov.noaa.messageapi.requests.BaseRequest;
import gov.noaa.messageapi.responses.PublishResponse;


public class PublishRequest extends BaseRequest implements IRequest {

    public PublishRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("publisher", schema, container, protocol);
    }

    public PublishRequest(IRequest request) {
        super(request);
    }

    public PublishRequest getCopy() {
        return new PublishRequest(this);
    }

    public IResponse submit() {
        return new PublishResponse(this);
    }

}
