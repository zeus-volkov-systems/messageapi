package gov.noaa.messageapi.records.container;

import gov.noaa.messageapi.fieldsets.FieldSet;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IFieldSet;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IRelationship;

public class ContainerRecord implements IContainerRecord {

    private List<IFieldSet> fieldSets = null;
    private List<IRelationship> relationships = null;
    private List<ICondition> conditions = null;

    public ContainerRecord(List<IFieldSet> fieldSets) {
        setFieldSets(fieldSets);
    }

    public ContainerRecord(IContainerRecord containerRecord) {
        setFieldSets(containerRecord.getFieldSets());
        setRelationships(containerRecord.getRelationships());
        setConditions(containerRecord.getConditions());
    }

    public ContainerRecord getCopy() {
        return new ContainerRecord(this);
    }

    public List<IFieldSet> getFieldSets() {
        return this.fieldSets;
    }

    public List<IRelationship> getRelationships() {
        return this.relationships;
    }

    public List<ICondition> getConditions() {
        return this.conditions;
    }

    private void setFieldSets(List<IFieldSet> fieldSets) {
        this.fieldSets = fieldSets.stream().map(fieldSet -> {
            return fieldSet.getCopy();
        }).collect(Collectors.toList());
    }

    private void setRelationships(List<IRelationship> relationships) {
        this.relationships = relationships;
    }

    private void setConditions(List<ICondition> conditions) {
        this.conditions = conditions;
    }
}
