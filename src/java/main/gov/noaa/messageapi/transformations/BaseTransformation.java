package gov.noaa.messageapi.transformations;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ITransformation;

public class BaseTransformation {

    private String id;
    private String type;

    public BaseTransformation(Map<String,Object> transformationMap) {
        setId((String) transformationMap.get("id"));
        setType((String) transformationMap.get("type"));
    }

    public BaseTransformation(ITransformation transformation) {
        setId(transformation.getId());
        setType(transformation.getType());
    }

    public String getId() {
        return this.id;
    }

    public String getType() {
        return this.type;
    }

    private void setId(String id) {
        this.id = id;
    }

    private void setType(String type) {
        this.type = type;
    }
}
