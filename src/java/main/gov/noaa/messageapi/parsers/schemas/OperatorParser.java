package gov.noaa.messageapi.parsers.schemas;

import gov.noaa.messageapi.interfaces.IOperatorFactory;

public class OperatorParser {

    public static IOperatorFactory build(String operatorClass) throws Exception {
        try {
            return (IOperatorFactory) constructPlugin(Class.forName(operatorClass));
        } catch (Exception e) {
            return null;
        }
    }

    private static Object constructPlugin(Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
