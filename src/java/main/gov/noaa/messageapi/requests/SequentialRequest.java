package gov.noaa.messageapi.requests;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IProtocol;

import gov.noaa.messageapi.responses.SequentialResponse;


/**
 * @author Ryan Berkheimer
 */
public class SequentialRequest extends BaseRequest implements IRequest {

    public SequentialRequest(final ISchema schema, final IContainer container, final IProtocol protocol) {
        super("sequential", schema, container, protocol);
    }

    public SequentialRequest(final IRequest request) {
        super(request);
    }

    public SequentialRequest(final IRequest request, final List<String> copyComponents) {
        super(request, copyComponents);
    }

    public SequentialRequest getCopy() {
        return new SequentialRequest(this);
    }

    public SequentialRequest getCopy(final List<String> copyComponents) {
        return new SequentialRequest(this, copyComponents);
    }

    public IResponse submit() {
        return new SequentialResponse(this);
    }

}
