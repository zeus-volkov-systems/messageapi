package gov.noaa.messageapi.records.container;

import java.util.UUID;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IRelationship;

public class ContainerRecord implements IContainerRecord {

    private UUID id = null;
    private List<ICollection> collections = null;
    private List<IRelationship> relationships = null;
    private List<ICondition> conditions = null;

    public ContainerRecord(List<ICollection> collections) {
        generateId();
        setCollections(collections);
    }

    public ContainerRecord(IContainerRecord containerRecord) {
        generateId();
        setCollections(containerRecord.getCollections());
        setRelationships(containerRecord.getRelationships());
        setConditions(containerRecord.getConditions());
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

    public List<IRelationship> getRelationships() {
        return this.relationships;
    }

    public List<ICondition> getConditions() {
        return this.conditions;
    }

    private void generateId() {
        this.id = UUID.randomUUID();
    }

    private void setCollections(List<ICollection> collections) {
        this.collections = collections.stream().map(collection -> {
            return collection.getCopy();
        }).collect(Collectors.toList());
    }

    private void setRelationships(List<IRelationship> relationships) {
        this.relationships = relationships;
    }

    private void setConditions(List<ICondition> conditions) {
        this.conditions = conditions;
    }
}
