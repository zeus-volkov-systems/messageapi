package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.definitions.ProtocolDefinition;

public interface IProtocol extends IComponent {

    public void initialize(IContainer c, ISchema s);
    public ProtocolDefinition getDefinition();

}
