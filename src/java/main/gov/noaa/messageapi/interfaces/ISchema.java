package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IOperator;

import gov.noaa.messageapi.definitions.SchemaDefinition;

public interface ISchema extends IComponent {

    public SchemaDefinition getDefinition();
    public void initialize(IContainer c, IProtocol p);
    public IRecord createRecord();
    public IOperator getOperator(String type);

}
