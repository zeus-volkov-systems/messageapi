package gov.noaa.messageapi.interfaces;

//import gov.noaa.messageapi.interfaces.IRequest;

/**
 * ISession is the primary container of MessageAPI.
 * An ISession holds definitions for its three dimensions
 * (Schema, Container, and Protocol), and provides a mechanism
 * for creating requests based on these definitions.
 * Sessions are primarily used as RequestFactories. Typically,
 * ISessions in MessageAPI are created using JSON manifest files.
 * @author Ryan Berkheimer
 */
public interface ISession {

    /**
     * Creates a new Request derived from the Session. This Request
     * is created using the Schema, Container, and Protocol layers
     * defined by this Session.
     */
    public IRequest createRequest();

    /**
     * Returns the Container held by this Session.
     */
    public IContainer getContainer();

    /**
     * Returns the Protocol held by this Session.
     */
    public IProtocol getProtocol();

    /**
     * Returns the Schema held by this Session.
     */
    public ISchema getSchema();
}
