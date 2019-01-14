package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.SimpleOperator;

public class FloatOperator extends SimpleOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Float f1 = new Float((Float) field.getValue());
        Float f2 = new Float((Float) condition.getValue());
        return Float.compare(f1, f2);
    }

}
