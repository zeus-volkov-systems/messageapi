package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public interface IConditionOperator {

    public boolean compare(IField field, ICondition condition);
}
