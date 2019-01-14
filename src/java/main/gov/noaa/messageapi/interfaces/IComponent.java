package gov.noaa.messageapi.interfaces;

import java.util.Map;

public interface IComponent {

    public String getType();
    public Map<String,Object> getProperties();

    public IComponent getCopy();

    public Object getProperty(String key);
    public boolean hasProperty(String key);

}
