package gov.noaa.messageapi.interfaces;

/**
 * IConditions are filtering tools that can operate on things like
 * IRecords or IRequests. To illustrate - 
 * 
 * in the SequentialSession, individual Records may set a value for any
 * Condition in the global set - the set conditions are then evaluated
 * on that Record to filter and/or reject that record.
 * Alternatively, Requests may set values on any global Condition, and
 * then Conditions may be referenced as qualifiers on Collections. In this
 * case, all records are evaluated on conditions set on every collection
 * to determine if it will be part of that container.
 * 
 * IConditions themselves are defined outside of code, in a spec,
 * that must be globally unique to a given ISession.
 * 
 * Conditions can be of different kinds (like a ComparisonCondition or
 * CompositeCondition).
 * @author Ryan Berkheimer
 */
public interface ICondition {

    /**
     * Returns the string ID of the condition.
     * Conditions must have globally-unique ids
     * in the context of a session.
     */
    public String getId();

    /**
     * Returns the type of the condition as a string.
     * The type should provide information for use in
     * condition value parsing and evaluation (for example,
     * type=composite, or type=comparison)
     */
    public String getType();

    /**
     * Returns the operator associated with the
     * condition as a string. The operator is something
     * that is used by the condition evaluator to know
     * how to make the comparison. For example, 
     */
    public String getOperator();

    /**
     * Returns the value of the condition. This value
     * should be related to something that the condition
     * will operate on - it is generic to handle different
     * condition types (e.g., comparison or composite).
     */
    public Object getValue();

    /**
     * Sets the value on the condition. For example, if the
     * type of the condition is a comparison, the condition value
     * should typically be related to the field that it compares.
     */
    public void setValue(Object value);

}
