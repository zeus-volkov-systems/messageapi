package gov.noaa.messageapi.connections;

import java.util.Map;
import java.lang.reflect.Constructor;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IEndpoint;

/**
 * @author Ryan Berkheimer
 */
public class BaseConnection {

    private IEndpoint endpoint = null;
    private String endpointClass = null;
    private Map<String,Object> constructorMap = null;

    public BaseConnection(String endpointClass, Map<String,Object> constructorMap) throws Exception {
        this.setEndpointClass(endpointClass);
        this.setEndpointConstructor(constructorMap);
        this.setEndpoint(endpointClass, constructorMap);
    }

    public BaseConnection(IConnection connection) throws Exception {
        this.setEndpointClass(connection.getEndpointClass());
        this.setEndpointConstructor(connection.getEndpointConstructor());
        this.setEndpoint(this.getEndpointClass(), this.getEndpointConstructor());
    }

    public String getEndpointClass() {
        return this.endpointClass;
    }

    public Map<String,Object> getEndpointConstructor() {
        return this.constructorMap;
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

    private void setEndpointConstructor(Map<String,Object> constructorMap) {
        this.constructorMap = constructorMap;
    }

    private void setEndpointClass(String endpointClass) {
        this.endpointClass = endpointClass;
    }

    protected void setEndpoint(String endpointClass, Map<String,Object> constructorMap) throws Exception {
        this.endpoint = this.initializeConnection(endpointClass, constructorMap);
    }

}
