package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.IComparisonCondition;
import gov.noaa.messageapi.interfaces.ICompositeCondition;
import java.util.Map;

import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.conditions.ComparisonCondition;
import gov.noaa.messageapi.conditions.CompositeCondition;

/**
 * Creates new conditions for use in session/request/record building.
 * It should be able to produce conditions based on an input that match
 * a supported condition type used by request and record processing.
 */
public class ConditionTypeFactory {

    public static ICondition create(Map<String,Object> conditionMap) throws Exception {
        switch((String) conditionMap.get("type")) {
            case "comparison":
                return new ComparisonCondition(conditionMap);
            case "composite":
                return new CompositeCondition(conditionMap);
        }
        return null;
    }

    public static ICondition create(ICondition condition) throws Exception {
        switch(condition.getType()) {
            case "comparison":
                return new ComparisonCondition((IComparisonCondition) condition);
            case "composite":
                return new CompositeCondition((ICompositeCondition) condition);
        }
        return null;
    }

}
