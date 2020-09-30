package gov.noaa.messageapi.operators;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.exceptions.MessageApiException;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * This comparison condition class contains various string comparisons.
 * Currently supported are '=', '/=', and 'contains'. These must be specified
 * in the constructor with the 'comparison' key (e.g., {'comparison':'='}).
 * @author Ryan Berkheimer
 */
public class StringConditionOperator implements IConditionOperator {

    private String comparison = null;

    public StringConditionOperator(Map<String,Object> params) throws Exception {
        try {
            this.setComparison((String)params.get("comparison"));
        } catch (Exception e) {
            throw new MessageApiException("The StringConditionOperator operator class needs a constructor parameter 'comparison'." +
                                            "Failed to initialize this condition.");
        }
    }

    public boolean compare(final IField field, final ICondition condition) {
        switch (this.comparison) {
            case "=":
                return this.isEqual((String) field.getValue(), (String) condition.getValue());
            case "/=":
                return this.isNotEqual((String) field.getValue(), (String) condition.getValue());
            case "contains":
                return this.contains((String) field.getValue(), (String) condition.getValue());
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

    private void setComparison(String comparison) {
        this.comparison = comparison;
    }

}
