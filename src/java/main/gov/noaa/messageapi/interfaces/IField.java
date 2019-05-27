package gov.noaa.messageapi.interfaces;

/**
 * @author Ryan Berkheimer
 */
public interface IField {

    public String getId();
    public String getName();
    public String getType();
    public boolean isRequired();
    public boolean isValid();
    public Object getValue();
    public void setValue(Object value);
    public void setValid(boolean valid);
    public void setType(String type);

}
