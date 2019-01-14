package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.SimpleOperator;

public class BooleanOperator extends SimpleOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Boolean b1 = new Boolean((Boolean) field.getValue());
        Boolean b2 = new Boolean((Boolean) condition.getValue());
        return Boolean.compare(b1, b2);
    }
}
