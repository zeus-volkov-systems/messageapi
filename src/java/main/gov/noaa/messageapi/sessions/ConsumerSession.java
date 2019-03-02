package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;

import gov.noaa.messageapi.sessions.DefaultSession;
import gov.noaa.messageapi.requests.ConsumeRequest;

public class ConsumerSession extends DefaultSession implements ISession {

    public ConsumerSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    public IRequest createRequest() {
        return new ConsumeRequest(this.schema, this.container, this.protocol);
    }


}
