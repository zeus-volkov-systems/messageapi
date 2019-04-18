package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IConditionOperator;

public interface IConditionOperatorFactory {

    public IConditionOperator getOperator(String type);

    public IConditionOperatorFactory getCopy();
}
