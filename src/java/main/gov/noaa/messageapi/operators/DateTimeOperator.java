package gov.noaa.messageapi.operators;

import java.util.Date;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public class DateTimeOperator extends SimpleOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Date d1 = (Date) field.getValue();
        Date d2 = (Date) condition.getValue();
        return d1.compareTo(d2);
    }
}
