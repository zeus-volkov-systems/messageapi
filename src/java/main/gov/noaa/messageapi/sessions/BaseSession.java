package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;

import gov.noaa.messageapi.parsers.plugins.SessionPluginParser;


/**
 * @author Ryan Berkheimer
 */
public class BaseSession {

    private IContainer container;
    private IProtocol protocol;
    private ISchema schema;

    public BaseSession(IContainer c, IProtocol p, ISchema s) {
        this.setContainer(c);
        this.setProtocol(p);
        this.setSchema(s);
        this.initialize(c, p, s);
    }

    public BaseSession(String spec) throws Exception {
        ISession session = new SessionPluginParser(spec).build();
        this.setContainer(session.getContainer());
        this.setProtocol(session.getProtocol());
        this.setSchema(session.getSchema());
    }

    public IContainer getContainer() {
        return this.container;
    }

    public ISchema getSchema() {
        return this.schema;
    }

    public IProtocol getProtocol() {
        return this.protocol;
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
