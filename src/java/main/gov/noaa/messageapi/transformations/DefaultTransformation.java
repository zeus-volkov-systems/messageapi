package gov.noaa.messageapi.transformations;

import java.util.Map;

import gov.noaa.messageapi.transformations.BaseTransformation;
import gov.noaa.messageapi.interfaces.ITransformation;

public class DefaultTransformation extends BaseTransformation implements ITransformation {

    private String parent;
    private String child;
    private String field;

    public DefaultTransformation(Map<String,Object> transformationMap) {
        super(transformationMap);
        setParent((String) transformationMap.get("parent"));
        setChild((String) transformationMap.get("child"));
        setField((String) transformationMap.get("field"));
    }

    public DefaultTransformation(ITransformation transformation) {
        super(transformation);
        setParent(transformation.getParent());
        setChild(transformation.getChild());
        setField(transformation.getField());
    }

    public String getParent() {
        return this.parent;
    }

    public String getChild() {
        return this.child;
    }

    public String getField() {
        return this.field;
    }

    private void setParent(String parent) {
        this.parent = parent;
    }

    private void setChild(String child) {
        this.child = child;
    }

    private void setField(String field) {
        this.field = field;
    }

}
