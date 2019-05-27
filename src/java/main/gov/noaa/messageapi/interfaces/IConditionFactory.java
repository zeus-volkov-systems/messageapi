package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IConditionOperator;

/**
 * @author Ryan Berkheimer
 */
public interface IConditionFactory {

    public IConditionOperator getOperator(String type);

    public IConditionFactory getCopy();
}
