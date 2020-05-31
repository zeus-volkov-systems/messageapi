package gov.noaa.messageapi.transformations;

import java.util.Map;

/**
 * The abstract base class for user transformations. This class provides extending user
 * endpoints the convenience of parsing and provides all possible generic default methods.
 * @author Ryan Berkheimer
 */
public abstract class BaseTransformation {

    public Map<String,Object> constructorMap = null;

    public BaseTransformation(Map<String,Object> parameters) {
        this.setConstructor(parameters);
    }

    public Map<String,Object> getConstructor() {
        return this.constructorMap;
    }

    private void setConstructor(Map<String, Object> constructorMap) {
        this.constructorMap = constructorMap;
    }

}