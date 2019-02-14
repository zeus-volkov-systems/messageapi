package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.operators.SimpleOperator;

public class DoubleOperator extends SimpleOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Double d1 = new Double((Double) field.getValue());
        Double d2 = new Double((Double) condition.getValue());
        return Double.compare(d1, d2);
    }

}
