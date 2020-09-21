package gov.noaa.messageapi.interfaces;

import java.util.Map;

/**
 * An IComponent is a base interface for principal system components (Schema, Container, Protocol).
 * Each of these component interfaces extend this base interface.
 * @author Ryan Berkheimer
 */
public interface IComponent {

    public String getType();
    public IMetadata getMetadata();
    public Map<String,Object> getProperties();

    public IComponent getCopy();

    public Object getProperty(String key);
    public boolean hasProperty(String key);

}
