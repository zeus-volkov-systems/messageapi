package gov.noaa.messageapi.relationships;

import java.util.Map;

import gov.noaa.messageapi.relationships.BaseRelationship;
import gov.noaa.messageapi.interfaces.IRelationship;

public class DefaultRelationship extends BaseRelationship implements IRelationship {

    private String parent;
    private String child;
    private String field;

    public DefaultRelationship(Map<String,Object> relationshipMap) {
        super(relationshipMap);
        setParent((String) relationshipMap.get("parent"));
        setChild((String) relationshipMap.get("child"));
        setField((String) relationshipMap.get("field"));
    }

    public DefaultRelationship(IRelationship relationship) {
        super(relationship);
        setParent(relationship.getParent());
        setChild(relationship.getChild());
        setField(relationship.getField());
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
