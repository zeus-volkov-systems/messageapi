package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;

public interface ISession {

    public IRequest createAddRequest();
    public IRequest createUpdateRequest();
    public IRequest createRemoveRequest();
    public IRequest createGetRequest();
    public IResponse submitRequest(IRequest request);

}
