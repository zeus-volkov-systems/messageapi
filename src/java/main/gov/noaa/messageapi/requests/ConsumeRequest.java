package gov.noaa.messageapi.requests;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;


/**
 * @author Ryan Berkheimer
 */
public class ConsumeRequest extends BaseRequest implements IRequest {

    public ConsumeRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("consumer", schema, container, protocol);
    }

    public ConsumeRequest(IRequest request) {
        super(request);
    }

    public ConsumeRequest getCopy() {
        return new ConsumeRequest(this);
    }

    public void process(IResponse response) {}


}
