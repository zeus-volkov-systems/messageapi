package gov.noaa.messageapi.sessions;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.requests.ParallelRequest;

/**
 * A parallel session is used for producing parallel requests.
 * The request is clean, in the sense that a new request gets its own copy of session
 * properties on creation - and is publish focused, in the sense that the request
 * is designed for publishing data to arbitrary endpoints through a protocol.
 * @author Ryan Berkheimer
 */
public class ParallelSession extends BaseSession implements ISession {

    /**
     * Constructs a new publish session from existing container, protocol, and
     * schema objects.
     * @param c An IContainer object
     * @param p An IProtocol object
     * @param s An ISchema object
     */
    public ParallelSession(final IContainer c, final IProtocol p, final ISchema s) throws Exception {
        super(c, p, s);
    }

    /**
     * Constructs a new publish session from existing session.
     * @param session A preexisting ISession object
     */
    public ParallelSession(final ISession session) throws Exception {
        super(session);
    }

    public ParallelSession(final Map<String,Object> sessionMap) throws Exception {
        super(sessionMap);
    }

    /**
     * Constructs a new publish session directly from a text map. The text map
     * should contain all the properties needed for Session Construction.
     * 
     * @param sessionSpec A text based map containing session construction
     *                    parameters
     * @throws Exception Throws exception if error creating session
     */
    public ParallelSession(final String sessionSpec) throws Exception {
        super(sessionSpec);
    }

    /**
     * Creates a clean publish request (deep copy), using the session parameters for the
     * request constructor
     * @return returns the created request
     */
    public IRequest createRequest() {
        return new ParallelRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

}
