package gov.noaa.messageapi.interfaces;

import java.util.UUID;
import java.util.List;

/**
 * A container record is an intermediate (factored) record that belongs in a one-to-one
 * relationship with containers. Containers are principal session components.
 * @author Ryan Berkheimer
 */
public interface IContainerRecord {

    public UUID getId();
    public List<ICollection> getCollections();
    public List<ITransformation> getTransformations();
    public IContainerRecord getCopy();

}
