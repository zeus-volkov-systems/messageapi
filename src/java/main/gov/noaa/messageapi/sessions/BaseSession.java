package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IContainer;

import gov.noaa.messageapi.parsers.plugins.SessionPluginParser;


/**
 * @author Ryan Berkheimer
 */
public class BaseSession {

    private IContainer container;
    private IProtocol protocol;
    private ISchema schema;

    public BaseSession(final IContainer c, final IProtocol p, final ISchema s) {
        this.setContainer(c);
        this.setProtocol(p);
        this.setSchema(s);
        this.initialize(c, p, s);
    }

    public BaseSession(final ISession session) {
        this.setContainer(session.getContainer());
        this.setProtocol(session.getProtocol());
        this.setSchema(session.getSchema());
    }

    public BaseSession(final Map<String,Object> sessionMap) throws Exception {
        final ISession session = new SessionPluginParser(sessionMap).build();
        this.setContainer(session.getContainer());
        this.setProtocol(session.getProtocol());
        this.setSchema(session.getSchema());
    }

    public BaseSession(final String spec) throws Exception {
        final ISession session = new SessionPluginParser(spec).build();
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

    private void initialize(final IContainer c, final IProtocol p, final ISchema s) {
        c.initialize(p, s);
        p.initialize(c, s);
        s.initialize(c, p);
    }

    private void setContainer(final IContainer c) {
        this.container = c;
    }

    private void setProtocol(final IProtocol p) {
        this.protocol = p;
    }

    private void setSchema(final ISchema s) {
        this.schema = s;
    }

}
