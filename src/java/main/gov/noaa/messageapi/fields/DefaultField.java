package gov.noaa.messageapi.fields;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IField;

/**
 * A field is a base unit of a record. Fields contain a required set of
 * properties on creation including a unique name,
 * a type (string, boolean, integer, etc), and whether or not the field is required.
 * The field also holds a value, which is assigned by the user during request creation
 * or accessed by the user during response parsing.
 */
public class DefaultField implements IField {

    private String id = null;
    private String type = null;
    private Boolean required = false;
    private Object value = null;
    private Boolean valid = true;

    public DefaultField(Map<String, Object> fieldMap) {
        this.id = (String) fieldMap.get("id");
        this.type = (String) fieldMap.get("type");
        this.required = (boolean) fieldMap.get("required");
    }

    public DefaultField(String id) {
        this.id = id;
    }

    public DefaultField(IField field) {
        this.id = field.getId();
        this.type = field.getType();
        this.required = field.isRequired();
        this.valid = field.isValid();
        this.value = field.getValue();
    }

    public String getId(){
        return this.id;
    }

    public String getName(){
        return this.id;
    }

    public String getType(){
        return this.type;
    }

    public boolean isRequired() {
        return this.required;
    }

    public boolean isValid() {
        return this.valid;
    }

    public void setValid(boolean valid) {
        this.valid = valid;
    }

    public Object getValue() {
        return this.value;
    }

    public void setValue(Object value) {
        this.value = value;
    }

    public void setType(String type) {
        this.type = type;
    }

}
