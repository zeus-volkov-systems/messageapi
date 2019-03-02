package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.sessions.BaseSession;

public class DefaultSession extends BaseSession {

    public DefaultSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
        initializeSession(c,p,s);
    }

    private void initializeSession(IContainer c, IProtocol p, ISchema s) {
        s.initialize(c, p);
        p.initialize(c, s);
        c.initialize(p, s);
    }


}
