package gov.noaa.messageapi.conditions;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ICondition;

/**
 * The base class for conditions. Every condition holds an id, a type,
 * and an operator. The id is used for unique identification of the condition
 * during processing and validation, the type is either composite or comparison,
 * and the operator depends on type ('and' or 'or' for composites, arbitrary
 * for comparisons (default set is <,>,=,/=,<=,>=)).
 */
public class BaseCondition {

    private String id;
    private String type;
    private String operator;

    /**
     * Constructor for building a condition from a map.
     * This is generally used during session bootstrapping.
     * @param conditionMap A map holding the id, type, and operator for a condition.
     */
    public BaseCondition(Map<String,Object> conditionMap) {
        setId((String) conditionMap.get("id"));
        setType((String) conditionMap.get("type"));
        setOperator((String) conditionMap.get("operator"));
    }

    /**
     * Copy constructor for creating a new condition from an existing condition.
     * Used in immutable processing of records.
     * @param condition The original condition to copy.
     */
    public BaseCondition(ICondition condition) {
        setId(condition.getId());
        setType(condition.getType());
        setOperator(condition.getOperator());
    }

    /**
     * Returns the condition ID
     * @return condition ID
     */
    public String getId() {
        return this.id;
    }

    /**
     * Returns the condition type (comparison or composite)
     * @return condition type
     */
    public String getType() {
        return this.type;
    }

    /**
     * Returns the condition operator
     * @return condition operator
     */
    public String getOperator() {
        return this.operator;
    }

    private void setId(String id) {
        this.id = id;
    }

    private void setType(String type) {
        this.type = type;
    }

    private void setOperator(String operator) {
        this.operator = operator;
    }

}
