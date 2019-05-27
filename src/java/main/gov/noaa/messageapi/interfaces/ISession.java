package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IRequest;

/**
 * @author Ryan Berkheimer
 */
public interface ISession {

    public IRequest createRequest();
    public IContainer getContainer();
    public IProtocol getProtocol();
    public ISchema getSchema();
}
