package gov.noaa.messageapi.parsers.schemas;

import java.lang.reflect.Constructor;
import java.util.Map;

import gov.noaa.messageapi.interfaces.IConditionFactory;
import gov.noaa.messageapi.interfaces.IConditionOperator;

/**
 * @author Ryan Berkheimer
 */
public class ConditionOperatorParser {

    public static IConditionFactory buildFactory(final String operatorClass) throws Exception {
        try {
            return (IConditionFactory) constructPluginNoArgs(Class.forName(operatorClass));
        } catch (final Exception e) {
            System.err.println(String.format(
                    "Could not construct the ConditionOperatorFactory using the given class %s", operatorClass));
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    public static Class<IConditionOperator> buildOperatorClass(final String operatorClassName) throws Exception {
        try {
            return (Class<IConditionOperator>) Class.forName(operatorClassName);
        } catch (final Exception e) {
            System.err.println(String.format(
                    "Could not construct the ConditionOperatorFactory using the given class %s", operatorClassName));
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    public static IConditionOperator constructOperatorInstance(final Map<String, Object> operatorMap) throws Exception {
        if (operatorMap.containsKey("constructor")) {
            try {
                final Class<?>[] ctrClasses = { Map.class };
                final Object[] args = { operatorMap.get("constructor") };
                return (IConditionOperator) constructPluginWithArgs(
                        (Class<IConditionOperator>) operatorMap.get("class"), ctrClasses, args);
            } catch (final Exception e) {
                System.err.println("Exception thrown while building a condition operator with args: " + e.getMessage());
                System.exit(1);
                return null;
            }
        } else {
            try {
                return (IConditionOperator) constructPluginNoArgs((Class<IConditionOperator>) operatorMap.get("class"));
            } catch (final Exception e) {
                System.err.println("Exception thrown while building a condition operator without args: " + e.getMessage());
                System.exit(1);
                return null;
            }
        }
    }

    private static Object constructPluginNoArgs(final Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

    private static Object constructPluginWithArgs(final Class<?> pluginClass, final Class<?>[] ctrClasses, final Object[] args)
            throws Exception {
        final Constructor<?> constructor = pluginClass.getDeclaredConstructor(ctrClasses);
        return constructor.newInstance(args);
    }

}
