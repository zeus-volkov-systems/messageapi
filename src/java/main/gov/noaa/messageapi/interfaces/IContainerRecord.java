package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.ITransformation;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public interface IContainerRecord {

    public UUID getId();
    public List<ICollection> getCollections();
    public List<ITransformation> getTransformations();
    public List<ICondition> getConditions();
    public IContainerRecord getCopy();

}
