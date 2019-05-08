package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.conditions.SimpleConditionOperator;

public class FloatConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Float f1 = new Float((Float) field.getValue());
        Float f2 = new Float((Float) condition.getValue());
        return Float.compare(f1, f2);
    }

}