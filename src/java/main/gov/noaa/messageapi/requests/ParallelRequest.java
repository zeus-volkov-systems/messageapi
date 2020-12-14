package gov.noaa.messageapi.requests;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IProtocol;

import gov.noaa.messageapi.responses.ParallelResponse;


/**
 * A parallel request is returned by a parallel session to return a parallel response.
 * Parallelism in this context means that streams over record sets, containers, and endpoint connections
 * are given to the Java parallelStream handler to provide automatic threading for those nodes.
 * @author Ryan Berkheimer
 */
public class ParallelRequest extends BaseRequest implements IRequest {

    public ParallelRequest(final ISchema schema, final IContainer container, final IProtocol protocol) {
        super("parallel", schema, container, protocol);
    }

    public ParallelRequest(final IRequest request) {
        super(request);
    }

    public ParallelRequest(final IRequest request, final List<String> copyComponents) {
        super(request, copyComponents);
    }

    public ParallelRequest getCopy() {
        return new ParallelRequest(this);
    }

    public ParallelRequest getCopy(final List<String> copyComponents) {
        return new ParallelRequest(this, copyComponents);
    }

    public IResponse submit() {
        return new ParallelResponse(this);
    }

}
