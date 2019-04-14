package gov.noaa.messageapi.interfaces;


public interface ITransformation {

    public String getId();
    public String getType();
    public String getParent();
    public String getChild();
    public String getField();

}
