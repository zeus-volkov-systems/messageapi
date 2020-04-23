package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

/**
 * @author Ryan Berkheimer
 */
public interface IContainerRecord {

    public UUID getId();
    public List<ICollection> getCollections();
    public List<ITransformation> getTransformations();
    public IContainerRecord getCopy();

}
