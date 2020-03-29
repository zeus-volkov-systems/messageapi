package gov.noaa.messageapi.interfaces;

//import gov.noaa.messageapi.interfaces.IField;
//import gov.noaa.messageapi.interfaces.ICondition;

/**
 * A ConditionOperator provides a method for evaluating
 * a comparison between a given field and condition.
 * @author Ryan Berkheimer
 */
public interface IConditionOperator {

    /**
     * Returns true or false depending on the outcome of the
     * evaluation. If the comparison is favorable, returns true.
     * If the comparison is disfavorable, returns false.
     */
    public boolean compare(IField field, ICondition condition);
}
