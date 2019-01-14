package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public abstract class SimpleOperator {

    protected abstract Integer getCompareValue(IField field, ICondition condition);

    protected boolean compare(IField field, ICondition condition) {
        Integer compareValue = getCompareValue(field, condition);
        switch(condition.getOperator()) {
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

    private boolean isGreater(Integer retval) {
        if (retval > 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isLess(Integer retval) {
        if (retval < 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isEqual(Integer retval) {
        if (retval == 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isNotEqual(Integer retval) {
        if (!(retval == 0)) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isLessOrEqual(Integer retval) {
        if (retval < 0 || retval == 0) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isGreaterOrEqual(Integer retval) {
        if (retval > 0 || retval == 0) {
            return true;
        } else {
            return false;
        }
    }
}
