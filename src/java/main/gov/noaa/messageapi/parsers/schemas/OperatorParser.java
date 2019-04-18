package gov.noaa.messageapi.parsers.schemas;

import gov.noaa.messageapi.interfaces.IConditionOperatorFactory;

public class OperatorParser {

    public static IConditionOperatorFactory build(String operatorClass) throws Exception {
        try {
            return (IConditionOperatorFactory) constructPlugin(Class.forName(operatorClass));
        } catch (Exception e) {
            return null;
        }
    }

    private static Object constructPlugin(Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
