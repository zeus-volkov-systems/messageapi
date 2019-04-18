package gov.noaa.messageapi.parsers.schemas;

import gov.noaa.messageapi.interfaces.IConditionFactory;

public class ConditionOperatorParser {

    public static IConditionFactory build(String operatorClass) throws Exception {
        try {
            return (IConditionFactory) constructPlugin(Class.forName(operatorClass));
        } catch (Exception e) {
            System.err.println(String.format("Could not construct the ConditionOperatorFactory using the given class %s", operatorClass));
            return null;
        }
    }

    private static Object constructPlugin(Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
