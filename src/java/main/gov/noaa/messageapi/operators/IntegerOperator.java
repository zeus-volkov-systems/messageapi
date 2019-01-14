package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.SimpleOperator;

public class IntegerOperator extends SimpleOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Integer i1 = new Integer((Integer) field.getValue());
        Integer i2 = new Integer((Integer) condition.getValue());
        return Integer.compare(i1, i2);
    }
}
