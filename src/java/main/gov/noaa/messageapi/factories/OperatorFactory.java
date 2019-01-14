package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.IOperator;
import gov.noaa.messageapi.interfaces.IOperatorFactory;

import gov.noaa.messageapi.operators.BooleanOperator;
import gov.noaa.messageapi.operators.FloatOperator;
import gov.noaa.messageapi.operators.IntegerOperator;
import gov.noaa.messageapi.operators.StringOperator;
import gov.noaa.messageapi.operators.DateTimeOperator;

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
public class OperatorFactory implements IOperatorFactory {

    /**
     * Copy constructor accessor for accessing the copy constructor for an
     * Interfaced OperatorFactory.
     * @return A new OperatorFactory object
     */
    public IOperatorFactory getCopy() {
        return new OperatorFactory();
    }

    /**
     * Returns an operator based on a data type name as a string.
     * @param  type The type of operator to return
     * @return      A new operator based on the specified type
     */
    public IOperator getOperator(String type) {
        switch (type) {
            case "boolean":
                return new BooleanOperator();
            case "float":
                return new FloatOperator();
            case "integer":
                return new IntegerOperator();
            case "string":
                return new StringOperator();
            case "datetime":
                return new DateTimeOperator();
        }
        return null;
    }

}
