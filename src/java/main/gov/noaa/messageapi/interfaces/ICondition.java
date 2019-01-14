package gov.noaa.messageapi.interfaces;


public interface ICondition {

    public String getId();
    public String getType();
    public String getOperator();
    public Object getValue();

    public void setValue(Object value);

}
