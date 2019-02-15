package gov.noaa.messageapi.interfaces;

import java.util.List;

import gov.noaa.messageapi.interfaces.IFieldSet;
import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.interfaces.ICondition;

public interface IContainerRecord {

    public List<IFieldSet> getFieldSets();
    public List<IRelationship> getRelationships();
    public List<ICondition> getConditions();
    public IContainerRecord getCopy();

}
