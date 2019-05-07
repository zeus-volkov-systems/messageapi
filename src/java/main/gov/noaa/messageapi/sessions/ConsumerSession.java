package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;

import gov.noaa.messageapi.requests.ConsumeRequest;

public class ConsumerSession extends BaseSession implements ISession {

    public ConsumerSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    public ConsumerSession(String sessionSpec) throws Exception {
        super(sessionSpec);
    }

    public IRequest createRequest() {
        return new ConsumeRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

}
