package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class FactoryDoubleConditionOperator extends FactorySimpleConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        return super.compare(field, condition);
    }

    protected Integer getCompareValue(final IField field, final ICondition condition) {
        final Double d1 = Double.valueOf((Double) field.getValue());
        final Double d2 = Double.valueOf((Double) condition.getValue());
        return Double.compare(d1, d2);
    }

}
