package gov.noaa.messageapi.interfaces;

import java.util.List;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

public interface IRecord {

    public List<IField> getFields();
    public List<ICondition> getConditions();

    public IRecord getCopy();

    public void setField(Object field, Object value);
    public IField getField(String name);
    public void setFields(List<IField> fields);

    public void setCondition(Object condition, Object value);
    public ICondition getCondition(String id);
    public void setConditions(List<ICondition> conditions);

    public boolean isValid();
    public void setValid(boolean status);

}
