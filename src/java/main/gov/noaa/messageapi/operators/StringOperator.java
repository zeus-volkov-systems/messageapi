package gov.noaa.messageapi.operators;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public class StringOperator implements IOperator {

    public boolean compare(IField field, ICondition condition) {
        switch(condition.getOperator()) {
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
        }
        return false;
    }

    private boolean isEqual(String fieldValue, String conditionValue) {
        if (fieldValue.equals(conditionValue)) {
            return true;
        }
        return false;
    }

    private boolean isNotEqual(String fieldValue, String conditionValue) {
        if (!fieldValue.equals(conditionValue)) {
            return true;
        }
        return false;
    }

}
