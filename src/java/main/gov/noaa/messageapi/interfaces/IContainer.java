package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.definitions.ContainerDefinition;

/**
 * @author Ryan Berkheimer
 */
public interface IContainer extends IComponent {

    public void initialize(IProtocol p, ISchema s);
    public ContainerDefinition getDefinition();

}
