package gov.noaa.messageapi.interfaces;


public interface IRelationship {

    public String getId();
    public String getType();
    public String getParent();
    public String getChild();
    public String getField();

}
