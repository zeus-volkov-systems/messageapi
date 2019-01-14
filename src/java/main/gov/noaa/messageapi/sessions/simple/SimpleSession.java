package gov.noaa.messageapi.sessions.simple;

import gov.noaa.messageapi.responses.simple.SimpleResponse;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.sessions.BaseSession;

import gov.noaa.messageapi.factories.RequestFactory;

public class SimpleSession extends BaseSession implements ISession {

    public SimpleSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
        initializeSession(c,p,s);
    }

    public IRequest createAddRequest() {
        return this.createRequest("add");
    }

    public IRequest createUpdateRequest() {
        return this.createRequest("update");
    }

    public IRequest createRemoveRequest() {
        return this.createRequest("remove");
    }

    public IRequest createGetRequest() {
        return this.createRequest("get");
    }

    public IResponse submit(IRequest request) {
        IResponse response = this.createResponse(request);
        return response;
    }

    private IRequest createRequest(String type) {
        return RequestFactory.create(type, this.schema, this.container, this.protocol);
    }

    private IResponse createResponse(IRequest request) {
        return new SimpleResponse(request);
    }

    private void initializeSession(IContainer c, IProtocol p, ISchema s) {
        s.initialize(c, p);
        p.initialize(c, s);
        c.initialize(p, s);
    }


}
