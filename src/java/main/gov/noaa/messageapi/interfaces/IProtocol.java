package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.definitions.ProtocolDefinition;

/**
 * @author Ryan Berkheimer
 */
public interface IProtocol extends IComponent {

    public void initialize(IContainer c, ISchema s);
    public ProtocolDefinition getDefinition();
    public List<IConnection> getConnections();

}
