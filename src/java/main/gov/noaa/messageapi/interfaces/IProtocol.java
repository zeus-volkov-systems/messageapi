package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.definitions.ProtocolDefinition;

public interface IProtocol extends IComponent {

    public void initialize(IContainer c, ISchema s);
    public ProtocolDefinition getDefinition();
    public void process(List<IContainerRecord> containerRecords);

}
