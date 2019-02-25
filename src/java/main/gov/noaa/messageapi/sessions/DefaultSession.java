package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.responses.DefaultResponse;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.sessions.BaseSession;

public class DefaultSession extends BaseSession {

    public DefaultSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
        initializeSession(c,p,s);
    }

    public IResponse submitRequest(IRequest request) {
        IResponse response = this.createResponse(request);
        return response;
    }

    public IResponse createResponse(IRequest request) {
        return new DefaultResponse(request);
    }

    private void initializeSession(IContainer c, IProtocol p, ISchema s) {
        s.initialize(c, p);
        p.initialize(c, s);
        c.initialize(p, s);
    }


}
