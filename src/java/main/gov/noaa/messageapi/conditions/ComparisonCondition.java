package gov.noaa.messageapi.conditions;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IComparisonCondition;;

/**
 * A comparison condition is a condition type that holds basic/fundamental
 * comparisons - things like <,>,=,/=, etc.
 * Comparison condition extends the BaseCondition.
 * @author Ryan Berkheimer
 */
public class ComparisonCondition extends BaseCondition implements IComparisonCondition {

    private Object value = null;
    private String field = null;

    /**
     * Constructor for creating a new ComparisonCondition from a map.
     * This is usually used by the schema when bootstrapping a new session.
     * @param conditionMap A map holding all required condition parameters.
     */
    public ComparisonCondition(final Map<String, Object> conditionMap) {
        super(conditionMap);
        this.setField((String) conditionMap.get("field"));
        if (conditionMap.containsKey("value")) {
            this.setValue(conditionMap.get("value"));
        }
    }

    /**
     * Copy constructor for creating a new ComparisonCondition from an existing one.
     * This is generally used in immutable operations when creating new records
     * during request building.
     * 
     * @param condition The original condition to copy
     */
    public ComparisonCondition(final IComparisonCondition condition) {
        super(condition);
        this.setField(condition.getField());
        this.setValue(condition.getValue());
    }

    /**
     * Returns the value held by the condition. Values are generalized objects. The
     * value is cast during comparison operation against field values.
     * 
     * @return The value held by a condition as an object.
     */
    public Object getValue() {
        return this.value;
    }

    /**
     * The field (as a name string) referenced by the comparison condition. All
     * comparison conditions correspond to one field.
     * 
     * @return The field name corresponding the the field to which the condition
     *         applies
     */
    public String getField() {
        return this.field;
    }

    /**
     * Sets the condition value for the condition. Any object type is a valid value.
     * 
     * @param value The value to associate with the condition
     */
    public void setValue(final Object value) {
        this.value = value;
    }

    /**
     * Sets the field value for the condition. The field should be part of the
     * schema topology. The field is set here as a string.
     * 
     * @param field A field name corresponding to a schema field
     */
    private void setField(final String field) {
        this.field = field;
    }

}
