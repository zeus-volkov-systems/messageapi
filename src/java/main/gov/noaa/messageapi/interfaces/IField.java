package gov.noaa.messageapi.interfaces;

public interface IField {

    public String getName();
    public String getType();
    public boolean isRequired();
    public boolean isValid();
    public Object getValue();
    public void setValue(Object value);
    public void setValid(boolean valid);
    public void setType(String type);

}
