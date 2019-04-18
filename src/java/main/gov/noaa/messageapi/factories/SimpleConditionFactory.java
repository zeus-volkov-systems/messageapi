package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IConditionFactory;

import gov.noaa.messageapi.operators.conditions.BooleanConditionOperator;
import gov.noaa.messageapi.operators.conditions.FloatConditionOperator;
import gov.noaa.messageapi.operators.conditions.DoubleConditionOperator;
import gov.noaa.messageapi.operators.conditions.IntegerConditionOperator;
import gov.noaa.messageapi.operators.conditions.StringConditionOperator;
import gov.noaa.messageapi.operators.conditions.DateTimeConditionOperator;

/**
 * Creates new Operators for use in comparison between conditions and fields attached to
 * schema records. This factory is bootstrapped during session creation by the
 * schema - this makes it customizable by the user for use in creating custom
 * operators and operator values.
 *
 * This particular factory should be treated
 * as a default or template - it can handle a variety of simple value types,
 * including booleans, floats, integers, strings, and datetimes.
 *
 * If other user value types are to be handled by this library, this operator factory
 * can be extended, replaced, or supplanted by a user factory to handle things
 * such as custom object type comparisons. Every operator that this possible returns
 * should extend the IOperator interface.
 */
public class SimpleConditionFactory implements IConditionFactory {

    /**
     * Copy constructor accessor for accessing the copy constructor for an
     * Interfaced OperatorFactory.
     * @return A new OperatorFactory object
     */
    public IConditionFactory getCopy() {
        return new SimpleConditionFactory();
    }

    /**
     * Returns an operator based on a data type name as a string.
     * @param  type The type of operator to return
     * @return      A new operator based on the specified type
     */
    public IConditionOperator getOperator(String type) {
        switch (type) {
            case "boolean":
                return new BooleanConditionOperator();
            case "float":
                return new FloatConditionOperator();
            case "double":
                return new DoubleConditionOperator();
            case "integer":
                return new IntegerConditionOperator();
            case "string":
                return new StringConditionOperator();
            case "datetime":
                return new DateTimeConditionOperator();
        }
        return null;
    }

}
