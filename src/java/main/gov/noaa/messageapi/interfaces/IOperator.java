package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public interface IOperator {

    public boolean compare(IField field, ICondition condition);
}
