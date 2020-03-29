package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
//import gov.noaa.messageapi.interfaces.IContainer;
//import gov.noaa.messageapi.interfaces.IProtocol;
//import gov.noaa.messageapi.interfaces.IRecord;
//import gov.noaa.messageapi.interfaces.IConditionOperator;

import gov.noaa.messageapi.definitions.SchemaDefinition;

/**
 * @author Ryan Berkheimer
 */
public interface ISchema extends IComponent {

    public SchemaDefinition getDefinition();
    public void initialize(IContainer c, IProtocol p);
    public IRecord createRecord();
    public IConditionOperator getOperator(String type);

}
