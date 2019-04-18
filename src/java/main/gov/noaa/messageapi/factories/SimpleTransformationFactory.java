package gov.noaa.messageapi.factories;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.ITransformation;
import gov.noaa.messageapi.interfaces.ITransformationFactory;

import gov.noaa.messageapi.transformations.JoinTransformation;
import gov.noaa.messageapi.transformations.ReduceTransformation;

public class SimpleTransformationFactory implements ITransformationFactory {

    /**
     * Returns an operator based on a data type name as a string.
     * @param  type The type of operator to return
     * @return      A new operator based on the specified type
     */
    public ITransformation getTransformation(String type, List<String> fields, Map<String,Object> params) {
        switch (type) {
            case "join":
                return new JoinTransformation(fields, params);
            case "reduce":
                return new ReduceTransformation(fields, params);
        }
        return null;
    }

}
