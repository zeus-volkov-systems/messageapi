package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IField;

public interface IFieldSet {

    public String getName();
    public String getNamespace();
    public List<IField> getFields();

}
