package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class BooleanConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Boolean b1 = Boolean.valueOf((Boolean) field.getValue());
        Boolean b2 = Boolean.valueOf((Boolean) condition.getValue());
        return Boolean.compare(b1, b2);
    }
}
