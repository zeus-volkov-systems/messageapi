package gov.noaa.messageapi.requests;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IProtocol;

import gov.noaa.messageapi.responses.DefaultResponse;


/**
 * @author Ryan Berkheimer
 */
public class DefaultRequest extends BaseRequest implements IRequest {

    public DefaultRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("default", schema, container, protocol);
    }

    public DefaultRequest(IRequest request) {
        super(request);
    }

    public DefaultRequest(IRequest request, List<String> copyComponents) {
        super(request, copyComponents);
    }

    public DefaultRequest getCopy() {
        return new DefaultRequest(this);
    }

    public DefaultRequest getCopy(List<String> copyComponents) {
        return new DefaultRequest(this, copyComponents);
    }

    public IResponse submit() {
        return new DefaultResponse(this);
    }

}
