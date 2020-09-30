package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.interfaces.IConditionFactory;

import gov.noaa.messageapi.operators.FactoryBooleanConditionOperator;
import gov.noaa.messageapi.operators.FactoryFloatConditionOperator;
import gov.noaa.messageapi.operators.FactoryDoubleConditionOperator;
import gov.noaa.messageapi.operators.FactoryIntegerConditionOperator;
import gov.noaa.messageapi.operators.FactoryStringConditionOperator;
import gov.noaa.messageapi.operators.FactoryDateTimeConditionOperator;

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
 * @author Ryan Berkheimer
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
    public IConditionOperator getOperator(final String type) {
        switch (type) {
            case "boolean":
                return new FactoryBooleanConditionOperator();
            case "float":
                return new FactoryFloatConditionOperator();
            case "double":
                return new FactoryDoubleConditionOperator();
            case "integer":
                return new FactoryIntegerConditionOperator();
            case "string":
                return new FactoryStringConditionOperator();
            case "datetime":
                return new FactoryDateTimeConditionOperator();
        }
        return null;
    }

}
