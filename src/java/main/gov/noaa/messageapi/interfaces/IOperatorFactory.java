package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IOperator;

public interface IOperatorFactory {

    public IOperator getOperator(String type);

    public IOperatorFactory getCopy();
}
