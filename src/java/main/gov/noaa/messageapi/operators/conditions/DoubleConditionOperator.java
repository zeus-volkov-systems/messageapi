package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class DoubleConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Double d1 = Double.valueOf((Double) field.getValue());
        Double d2 = Double.valueOf((Double) condition.getValue());
        return Double.compare(d1, d2);
    }

}
