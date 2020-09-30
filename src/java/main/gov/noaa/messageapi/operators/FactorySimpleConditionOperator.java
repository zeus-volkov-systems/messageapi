package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public abstract class FactorySimpleConditionOperator {

    protected abstract Integer getCompareValue(IField field, ICondition condition);

    protected boolean compare(final IField field, final ICondition condition) {
        final Integer compareValue = getCompareValue(field, condition);
        switch (condition.getOperator()) {
            case ">":
                return isGreater(compareValue);
            case "<":
                return isLess(compareValue);
            case ">=":
                return isGreaterOrEqual(compareValue);
            case "<=":
                return isLessOrEqual(compareValue);
            case "=":
                return isEqual(compareValue);
            case "/=":
                return isNotEqual(compareValue);
        }
        return false;
    }

    private boolean isGreater(final Integer retval) {
        if (retval > 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isLess(final Integer retval) {
        if (retval < 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isEqual(final Integer retval) {
        if (retval == 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isNotEqual(final Integer retval) {
        if (!(retval == 0)) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isLessOrEqual(final Integer retval) {
        if (retval < 0 || retval == 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isGreaterOrEqual(final Integer retval) {
        if (retval > 0 || retval == 0) {
            return true;
        } else {
            return false;
        }
    }
}
