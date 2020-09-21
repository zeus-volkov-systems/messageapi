package gov.noaa.messageapi.parsers.schemas;

import gov.noaa.messageapi.interfaces.IConditionFactory;

/**
 * @author Ryan Berkheimer
 */
public class ConditionOperatorParser {

    public static IConditionFactory build(final String operatorClass) throws Exception {
        try {
            return (IConditionFactory) constructPlugin(Class.forName(operatorClass));
        } catch (final Exception e) {
            System.err.println(String.format(
                    "Could not construct the ConditionOperatorFactory using the given class %s", operatorClass));
            return null;
        }
    }

    private static Object constructPlugin(final Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
