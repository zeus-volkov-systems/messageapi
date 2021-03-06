package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class FactoryBooleanConditionOperator extends FactorySimpleConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(final IField field, final ICondition condition) {
        final Boolean b1 = Boolean.valueOf((Boolean) field.getValue());
        final Boolean b2 = Boolean.valueOf((Boolean) condition.getValue());
        return Boolean.compare(b1, b2);
    }
}
