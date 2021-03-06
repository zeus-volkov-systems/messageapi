package gov.noaa.messageapi.fields;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IField;

/**
 * A field is a base unit of a record. Fields contain a required set of
 * properties on creation including a unique name,
 * a type (string, boolean, integer, etc), and whether or not the field is required.
 * The field also holds a value, which is assigned by the user during request creation
 * or accessed by the user during response parsing.
 * @author Ryan Berkheimer
 */
public class DefaultField implements IField {

    private String id = null;
    private String type = null;
    private Boolean required = false;
    private Object value = null;
    private Boolean valid = true;

    public DefaultField(final Map<String, Object> fieldMap) {
        if (fieldMap.containsKey("id")) {
            this.id = (String) fieldMap.get("id");
        }
        if (fieldMap.containsKey("type")) {
            this.type = (String) fieldMap.get("type");
        }
        if (fieldMap.containsKey("required")) {
            this.required = (boolean) fieldMap.get("required");
        }
        if (fieldMap.containsKey("value")) {
            this.value = fieldMap.get("value");
        }
    }

    public DefaultField(final String id) {
        this.id = id;
    }

    public DefaultField(final String id, final String type, final Boolean required, final Object value,
            final Boolean valid) {
        this.id = id;
        this.type = type;
        this.required = required;
        this.value = value;
        this.valid = valid;
    }

    public DefaultField(final IField field) {
        this.id = field.getId();
        this.type = field.getType();
        this.required = field.isRequired();
        this.valid = field.isValid();
        this.value = field.getValue();
    }

    public String getId() {
        return this.id;
    }

    public String getName() {
        return this.id;
    }

    public String getType() {
        return this.type;
    }

    public boolean isRequired() {
        return this.required;
    }

    public boolean isValid() {
        return this.valid;
    }

    public void setValid(final Boolean valid) {
        this.valid = valid;
    }

    public Object getValue() {
        return this.value;
    }

    public void setValue(final Object value) {
        this.value = value;
    }

    public void setType(final String type) {
        this.type = type;
    }

}
