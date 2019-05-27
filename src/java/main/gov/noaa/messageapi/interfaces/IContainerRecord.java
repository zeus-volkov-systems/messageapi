package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.ITransformation;

/**
 * @author Ryan Berkheimer
 */
public interface IContainerRecord {

    public UUID getId();
    public List<ICollection> getCollections();
    public List<ITransformation> getTransformations();
    public IContainerRecord getCopy();

}
