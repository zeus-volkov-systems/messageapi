package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.conditions.SimpleConditionOperator;

/**
 * @author Ryan Berkheimer
 */
public class IntegerConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        //Integer i1 = new Integer((Integer) field.getValue());
        Integer i1 = Integer.valueOf((Integer) field.getValue());
        //Integer i2 = new Integer((Integer) condition.getValue());
        Integer i2 = Integer.valueOf((Integer) condition.getValue());
        return Integer.compare(i1, i2);
    }
}
