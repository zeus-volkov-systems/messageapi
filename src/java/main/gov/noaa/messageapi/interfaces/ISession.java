package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IRequest;

public interface ISession {

    public IRequest createRequest();
    public IContainer getContainer();
    public IProtocol getProtocol();
    public ISchema getSchema();
}
