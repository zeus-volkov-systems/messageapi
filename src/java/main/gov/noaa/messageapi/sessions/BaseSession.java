package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;

public class BaseSession {

    protected IContainer container;
    protected IProtocol protocol;
    protected ISchema schema;

    public BaseSession(IContainer c, IProtocol p, ISchema s) {
        setContainer(c);
        setProtocol(p);
        setSchema(s);
        initialize(c, p, s);
    }

    private void initialize(IContainer c, IProtocol p, ISchema s) {
        c.initialize(p, s);
        p.initialize(c, s);
        s.initialize(c, p);
    }

    private void setContainer(IContainer c) {
        this.container = c;
    }

    private void setProtocol(IProtocol p) {
        this.protocol = p;
    }

    private void setSchema(ISchema s) {
        this.schema = s;
    }


}
