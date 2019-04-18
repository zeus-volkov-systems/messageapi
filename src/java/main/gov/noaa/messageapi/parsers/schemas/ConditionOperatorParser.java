package gov.noaa.messageapi.parsers.schemas;

import gov.noaa.messageapi.interfaces.IConditionFactory;

public class ConditionOperatorParser {

    public static IConditionFactory build(String operatorClass) throws Exception {
        try {
            return (IConditionFactory) constructPlugin(Class.forName(operatorClass));
        } catch (Exception e) {
            return null;
        }
    }

    private static Object constructPlugin(Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
