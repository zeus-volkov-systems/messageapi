package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IConditionOperator;

public interface IConditionFactory {

    public IConditionOperator getOperator(String type);

    public IConditionFactory getCopy();
}
