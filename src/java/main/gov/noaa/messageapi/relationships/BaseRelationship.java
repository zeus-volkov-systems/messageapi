package gov.noaa.messageapi.relationships;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IRelationship;

public class BaseRelationship {

    private String id;
    private String type;

    public BaseRelationship(Map<String,Object> relationshipMap) {
        setId((String) relationshipMap.get("id"));
        setType((String) relationshipMap.get("type"));
    }

    public BaseRelationship(IRelationship relationship) {
        setId(relationship.getId());
        setType(relationship.getType());
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
