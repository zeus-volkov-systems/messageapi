package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;

import gov.noaa.messageapi.sessions.DefaultSession;
import gov.noaa.messageapi.requests.PublisherRequest;


public class PublisherSession extends DefaultSession implements ISession {

    public PublisherSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    public IRequest createRequest() {
        return new PublisherRequest(this.schema, this.container, this.protocol);
    }

    public IResponse submitRequest(IRequest request) {
        IResponse response = this.createResponse(request);
        return response;
    }

}
