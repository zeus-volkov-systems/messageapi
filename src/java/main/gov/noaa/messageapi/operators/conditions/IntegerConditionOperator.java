package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class IntegerConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(final IField field, final ICondition condition) {
        final Integer i1 = Integer.valueOf((Integer) field.getValue());
        final Integer i2 = Integer.valueOf((Integer) condition.getValue());
        return Integer.compare(i1, i2);
    }
}
