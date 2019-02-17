package gov.noaa.messageapi.interfaces;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IMetadata;

public interface IComponent {

    public String getType();
    public IMetadata getMetadata();
    public Map<String,Object> getProperties();

    public IComponent getCopy();

    public Object getProperty(String key);
    public boolean hasProperty(String key);

}
