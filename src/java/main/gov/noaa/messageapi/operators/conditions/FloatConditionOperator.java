package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class FloatConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(final IField field, final ICondition condition) {
        final Float f1 = Float.valueOf((Float) field.getValue());
        final Float f2 = Float.valueOf((Float) condition.getValue());
        return Float.compare(f1, f2);
    }

}
