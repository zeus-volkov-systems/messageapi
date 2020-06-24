package gov.noaa.messageapi.interfaces;

import java.util.List;

/**
 * A composite condition is a type of condition that combines other
 * conditions. i.e., 'and' or 'or' are two types of composite conditions.
 * 'one of' could be another composite condition.
 * @author Ryan Berkheimer
 */
public interface ICompositeCondition extends ICondition {

    /**
     * Returns a list of all condition ids that are part of the composite condition
     */
    public List<String> getConditions();

}
