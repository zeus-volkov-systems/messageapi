package gov.noaa.messageapi.records.container;

import java.util.UUID;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IBin;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IRelationship;

public class ContainerRecord implements IContainerRecord {

    private UUID id = null;
    private List<IBin> bins = null;
    private List<IRelationship> relationships = null;
    private List<ICondition> conditions = null;

    public ContainerRecord(List<IBin> bins) {
        setID(UUID.randomUUID());
        setBins(bins);
    }

    public ContainerRecord(IContainerRecord containerRecord) {
        setID(containerRecord.getID());
        setBins(containerRecord.getBins());
        setRelationships(containerRecord.getRelationships());
        setConditions(containerRecord.getConditions());
    }

    public ContainerRecord getCopy() {
        return new ContainerRecord(this);
    }

    public UUID getID() {
        return this.id;
    }

    public List<IBin> getBins() {
        return this.bins;
    }

    public List<IRelationship> getRelationships() {
        return this.relationships;
    }

    public List<ICondition> getConditions() {
        return this.conditions;
    }

    private void setID(UUID uuid) {
        this.id = uuid;
    }

    private void setBins(List<IBin> bins) {
        this.bins = bins.stream().map(bin -> {
            return bin.getCopy();
        }).collect(Collectors.toList());
    }

    private void setRelationships(List<IRelationship> relationships) {
        this.relationships = relationships;
    }

    private void setConditions(List<ICondition> conditions) {
        this.conditions = conditions;
    }
}
