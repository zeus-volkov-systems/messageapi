package gov.noaa.messageapi.operators.conditions;

import java.util.Date;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public class DateTimeConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(IField field, ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(IField field, ICondition condition) {
        Date d1 = (Date) field.getValue();
        Date d2 = (Date) condition.getValue();
        return d1.compareTo(d2);
    }
}
