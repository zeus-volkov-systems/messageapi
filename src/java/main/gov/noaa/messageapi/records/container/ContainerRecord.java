package gov.noaa.messageapi.records.container;

import java.util.UUID;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.ITransformation;

/**
 * ContainerRecord is the standard container record for the DataAPI implementation
 * of MessageAPI. A Container record is primarily a container for collections,
 * which are reduced versions of SchemaRecords (Simple Field Collections).
 * ContainerRecords also hold transformations, which are implemented from the
 * transformation spec in the overall session. ContainerRecords must implement
 * the IContainerRecord.
 * @author Ryan Berkheimer
 */
public class ContainerRecord implements IContainerRecord {

    private UUID id = null;
    private List<ICollection> collections = null;
    private List<ITransformation> transformations = null;

    /**
     * Constructor for ContainerRecord that creates a new ContainerRecord
     * from an existing set of Collections.
     * @param collections Collections to be used in ContainerRecord construction
     */
    public ContainerRecord(List<ICollection> collections) {
        this.generateId();
        this.setCollections(collections);
    }

    public ContainerRecord(IContainerRecord containerRecord) {
        this.generateId();
        this.setCollections(containerRecord.getCollections());
        this.setTransformations(containerRecord.getTransformations());
    }

    public ContainerRecord(List<ICollection> collections, List<ITransformation> transformations) {
        this.generateId();
        this.setCollections(collections);
        this.setTransformations(transformations);
    }

    public ContainerRecord getCopy() {
        return new ContainerRecord(this);
    }

    public UUID getId() {
        return this.id;
    }

    public List<ICollection> getCollections() {
        return this.collections;
    }

    public List<ITransformation> getTransformations() {
        return this.transformations;
    }

    private void generateId() {
        this.id = UUID.randomUUID();
    }

    private void setCollections(List<ICollection> collections) {
        this.collections = collections.stream().map(collection -> {
            return collection.getCopy();
        }).collect(Collectors.toList());
    }

    private void setTransformations(List<ITransformation> transformations) {
        this.transformations = transformations;
    }

}
