package gov.noaa.messageapi.operators.conditions;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public class StringConditionOperator implements IConditionOperator {

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
