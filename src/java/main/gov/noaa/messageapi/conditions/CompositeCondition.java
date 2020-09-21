package gov.noaa.messageapi.conditions;

import java.util.List;
import java.util.Map;

import gov.noaa.messageapi.interfaces.ICompositeCondition;

/**
 * A composite condition is a condition that holds a list of other
 * condition (either composite or comparison) ids and and holds an operator
 * (either 'and' or 'or').
 * Composite conditions extend the BaseCondition.
 * @author Ryan Berkheimer
 */
public class CompositeCondition extends BaseCondition implements ICompositeCondition {

    private Object value = null;

    /**
     * Constructor for creating a new CompositeCondition from a map.
     * This is usually used by the schema when bootstrapping a new session.
     * @param conditionMap A map holding all required condition parameters.
     */
    public CompositeCondition(final Map<String, Object> conditionMap) {
        super(conditionMap);
        setValue(conditionMap.get("conditions"));
    }

    /**
     * Copy constructor for creating a new CompositeCondition from an existing one.
     * This is generally used in immutable operations when creating new records
     * during request building.
     * 
     * @param condition The original condition to copy
     */
    public CompositeCondition(final ICompositeCondition condition) {
        super(condition);
        setValue(condition.getConditions());
    }

    /**
     * sets the value for a composite condition. In a composite condition, the value
     * is a list of the ids of other conditions.
     * 
     * @param value A list of condition ids
     */
    public void setValue(final Object value) {
        this.value = value;
    }

    /**
     * Returns the list of condition Ids held by this condition as an object
     * @return The list of condition ids that make up this condition as an object
     */
    public Object getValue() {
        return this.value;
    }

    @SuppressWarnings("unchecked")
    /**
     * Returns the list of conditions held by this condition as a List of Strings.
     * This is a convenience method for getValue that performs the cast before returning.
     * @return A List of condition Ids held by this condition
     */
    public List<String> getConditions() {
        return (List<String>) this.value;
    }

}
