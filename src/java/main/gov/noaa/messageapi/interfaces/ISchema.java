package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.definitions.SchemaDefinition;
import gov.noaa.messageapi.enums.ConditionStrategy;

/**
 * @author Ryan Berkheimer
 */
public interface ISchema extends IComponent {

    public SchemaDefinition getDefinition();
    public void initialize(IContainer c, IProtocol p);
    public IRecord createRecord();
    public IConditionOperator getOperator(Enum<ConditionStrategy> strategy, String type);
    public Enum<ConditionStrategy> getConditionStrategy();

}
