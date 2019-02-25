package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;

public interface ISession {

    public IRequest createRequest();
    public IResponse submitRequest(IRequest request);

}
