package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;

import gov.noaa.messageapi.sessions.BaseSession;
import gov.noaa.messageapi.requests.PublishRequest;

/**
 * A publisher session is used for producing clean publish requests.
 * The request is clean, in the sense that a new request gets its own copy of session
 * properties on creation - and is publish focused, in the sense that the request
 * is designed for publishing data to arbitrary endpoints through a protocol.
 */
public class PublisherSession extends BaseSession implements ISession {

    /**
     * Constructs a new publish session from existing container, protocol, and
     * schema objects.
     * @param c An IContainer object
     * @param p An IProtocol object
     * @param s An ISchema object
     */
    public PublisherSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    /**
     * Constructs a new publish session directly from a text map. The text
     * map should contain all the properties needed for Session Construction.
     * @param  sessionSpec A text based map containing session construction parameters
     * @throws Exception   Throws exception if error creating session
     */
    public PublisherSession(String sessionSpec) throws Exception {
        super(sessionSpec);
    }

    /**
     * Creates a clean publish request, using the session parameters for the
     * request constructor
     * @return returns the created request
     */
    public IRequest createRequest() {
        return new PublishRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

}
