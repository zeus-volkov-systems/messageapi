package gov.noaa.messageapi.sessions;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;

import gov.noaa.messageapi.requests.ConsumeRequest;

/**
 * A consumer session is used for producing clean consumer requests.
 * The request is clean, in the sense that a new request gets its own copy of session
 * properties on creation - and is consumer focused, in the sense that the request
 * is designed for gathering data from the protocol.
 */
public class ConsumerSession extends BaseSession implements ISession {

    /**
     * Create a consumer session from existing container, protocol, and schema objects
     * @param c An IContainer object
     * @param p An IProtocol object
     * @param s An ISchema object
     */
    public ConsumerSession(IContainer c, IProtocol p, ISchema s) {
        super(c, p, s);
    }

    /**
     * Create a ConsumerSession from a session specification map.
     * @param  sessionSpec A Session map containing all session parameters.
     * @throws Exception   throws an exception if the session creation fails.
     */
    public ConsumerSession(String sessionSpec) throws Exception {
        super(sessionSpec);
    }

    /**
     * Creates a clean consume request, using the session parameters for the
     * request constructor
     * @return returns the created request
     */
    public IRequest createRequest() {
        return new ConsumeRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

}
