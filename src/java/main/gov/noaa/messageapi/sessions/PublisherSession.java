package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;

import gov.noaa.messageapi.sessions.BaseSession;
import gov.noaa.messageapi.requests.PublishRequest;


public class PublisherSession extends BaseSession implements ISession {

    public PublisherSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    public PublisherSession(String sessionSpec) throws Exception {
        super(sessionSpec);
    }

    public IRequest createRequest() {
        return new PublishRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

}
