package gov.noaa.messageapi.interfaces;


/**
 * ComparisonConditions represent value-checking comparisons.
 * These types of conditions are things like <, >, ==, contains.
 * ComparisonConditions correspond to Fields.
 * @author Ryan Berkheimer
 */
public interface IComparisonCondition extends ICondition {

    /**
     * Returns the Field ID/Name corresponding to the Condition
     */
    public String getField();

}
