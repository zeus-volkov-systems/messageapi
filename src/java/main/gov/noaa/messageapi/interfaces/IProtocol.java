package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;

public interface IProtocol extends IComponent {

    public void initialize(IContainer c, ISchema s);

}
