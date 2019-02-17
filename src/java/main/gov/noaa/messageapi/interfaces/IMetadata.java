package gov.noaa.messageapi.interfaces;

import java.util.Map;


public interface IMetadata {

    public String getId();
    public Object getVersion();
    public String getDescription();
    public Map<String,Object> getClassifiers();
    public Object getClassifier(String classifierKey);

}
