package gov.noaa.messageapi.operators.conditions;

import java.util.Date;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class DateTimeConditionOperator extends SimpleConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(final IField field, final ICondition condition) {
        final Date d1 = (Date) field.getValue();
        final Date d2 = (Date) condition.getValue();
        return d1.compareTo(d2);
    }
}
