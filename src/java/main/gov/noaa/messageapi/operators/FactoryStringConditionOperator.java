package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public class FactoryStringConditionOperator implements IConditionOperator {

    public boolean compare(final IField field, final ICondition condition) {
        switch (condition.getOperator()) {
            case ">":
                return false;
            case "<":
                return false;
            case ">=":
                return false;
            case "<=":
                return false;
            case "=":
                return isEqual((String) field.getValue(), (String) condition.getValue());
            case "/=":
                return isNotEqual((String) field.getValue(), (String) condition.getValue());
            case "contains":
                return contains((String) field.getValue(), (String) condition.getValue());
        }
        return false;
    }

    private boolean isEqual(final String fieldValue, final String conditionValue) {
        if (fieldValue.equals(conditionValue)) {
            return true;
        }
        return false;
    }

    private boolean isNotEqual(final String fieldValue, final String conditionValue) {
        if (!fieldValue.equals(conditionValue)) {
            return true;
        }
        return false;
    }

    private boolean contains(final String fieldValue, final String conditionValue) {
        if (fieldValue.contains(conditionValue)) {
            return true;
        } else {
            return false;
        }
    }

}
