package gov.noaa.messageapi.interfaces;

/**
 * The ConditionFactory interface provides a method for returning
 * an operator for a given condition type. The type is usually
 * something like 'boolean' or 'string' or a user defined type.
 * This factory pattern provides a stereotyped way to isolate
 * different types of field types for comparison within a given
 * session manifest.
 * @author Ryan Berkheimer
 */
public interface IConditionFactory {

    /**
     * Returns the operator object for a given field/condition type (e.g., boolean)
     */
    public IConditionOperator getOperator(String type);

    /**
     * Returns a deep-copy of the condition factory
     */
    public IConditionFactory getCopy();
}
