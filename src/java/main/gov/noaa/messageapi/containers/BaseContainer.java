package gov.noaa.messageapi.containers;

import java.util.Map;
import java.util.HashMap;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IMetadata;
import gov.noaa.messageapi.definitions.ContainerDefinition;

/**
 * @author Ryan Berkheimer
 */
public class BaseContainer {

    private Map<String, Object> properties;
    protected ContainerDefinition definition;
    protected IMetadata metadata = null;

    public BaseContainer(final Map<String, Object> properties) {
        setProperties(properties);
    }

    public BaseContainer(final IContainer container) {
        this.definition = new ContainerDefinition(container.getDefinition());
        this.properties = new HashMap<String, Object>(container.getProperties());
    }

    private void setProperties(final Map<String, Object> properties) {
        this.properties = properties;
    }

    public Map<String, Object> getProperties() {
        return this.properties;
    }

    public Object getProperty(final String key) {
        if (hasProperty(key)) {
            return this.properties.get(key);
        }
        return null;
    }

    public boolean hasProperty(final String key) {
        if (this.properties.containsKey(key)) {
            return true;
        }
        return false;
    }

    public ContainerDefinition getDefinition() {
        return this.definition;
    }

    public IMetadata getMetadata() {
        return this.metadata;
    }

    protected void createContainerDefinition(final Map<String, Object> properties) throws Exception {
        this.definition = new ContainerDefinition(properties);
    }
}
