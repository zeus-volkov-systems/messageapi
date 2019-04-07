package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

import gov.noaa.messageapi.interfaces.IBin;
import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.interfaces.ICondition;

public interface IContainerRecord {

    public UUID getId();
    public List<IBin> getBins();
    public List<IRelationship> getRelationships();
    public List<ICondition> getConditions();
    public IContainerRecord getCopy();

}
