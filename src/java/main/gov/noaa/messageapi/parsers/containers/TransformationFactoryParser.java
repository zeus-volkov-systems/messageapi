package gov.noaa.messageapi.parsers.containers;

import gov.noaa.messageapi.interfaces.ITransformationFactory;

public class TransformationFactoryParser {

    public static ITransformationFactory build(String transformationClass) throws Exception {
        try {
            return (ITransformationFactory) constructPlugin(Class.forName(transformationClass));
        } catch (Exception e) {
            System.err.println(String.format("Could not construct the TransformationFactory using the given class %s", transformationClass));
            return null;
        }
    }

    private static Object constructPlugin(Class<?> pluginClass) throws Exception {
        return pluginClass.getConstructor().newInstance();
    }

}
