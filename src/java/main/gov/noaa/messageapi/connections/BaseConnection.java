package gov.noaa.messageapi.connections;

import java.util.Map;
import java.lang.reflect.Constructor;

import gov.noaa.messageapi.interfaces.IEndpoint;

public class BaseConnection {

    private IEndpoint endpoint;

    public BaseConnection(String endpointClass, Map<String,Object> constructorMap) throws Exception {
        this.endpoint = initializeConnection(endpointClass, constructorMap);
    }

    protected IEndpoint getEndpoint() {
        return this.endpoint;
    }

    private IEndpoint initializeConnection(String endpoint, Map<String,Object> constructor) throws Exception {
        Class<?>[] ctrClasses = {Map.class};
        Object[] args = {constructor};
        return (IEndpoint) instantiateEndpoint(Class.forName(endpoint), ctrClasses, args);
    }

    private Object instantiateEndpoint(Class<?> pluginClass, Class<?>[] ctrClasses, Object[] args) throws Exception {
        Constructor<?> constructor = pluginClass.getDeclaredConstructor(ctrClasses);
        return constructor.newInstance(args);
    }

}
