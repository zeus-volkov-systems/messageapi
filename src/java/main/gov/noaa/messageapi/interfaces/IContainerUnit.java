package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;

public interface IContainerUnit {

    public String getName();
    public String getNamespace();
    public String getType();
    public List<IField> getFields();
    public List<IContainerUnit> getChildren();
    public IContainerUnit getCopy(IRecord record);

}
