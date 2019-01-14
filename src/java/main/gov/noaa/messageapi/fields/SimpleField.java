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
public class SimpleField implements IField {

    private String name = null;
    private String type = null;
    private Boolean required = null;
    private Object value = null;
    private Boolean valid = true;

    public SimpleField(Map<String, Object> fieldMap) {
        this.name = (String) fieldMap.get("name");
        this.type = (String) fieldMap.get("type");
        this.required = (boolean) fieldMap.get("required");
    }

    public SimpleField(String name) {
        this.name = name;
    }

    public SimpleField(IField field) {
        this.name = (String) field.getName();
        this.type = (String) field.getType();
        this.required = (boolean) field.isRequired();
        this.valid = (boolean) field.isValid();
        this.value = field.getValue();
    }

    public String getName(){
        return this.name;
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
