package gov.noaa.messageapi.records.container;

import java.util.ArrayList;
import java.util.List;

import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.utils.containers.RelationshipUtils;
import gov.noaa.messageapi.utils.containers.UnitUtils;

public class RootUnit extends BaseUnit implements IContainerUnit {

    public RootUnit(List<IContainerUnit> fieldUnits, List<IRelationship> relationships) {
        super("container");
        setChildren(fieldUnits, relationships);
    }

    public RootUnit(IRecord r) {

    }

    public RootUnit getCopy(IRecord r) {
        return new RootUnit(r);
    }

    private void setChildren(List<IContainerUnit> fieldUnits, List<IRelationship> relationships) {
        List<String> references = RelationshipUtils.getReferences(relationships);
        List<IContainerUnit> referencedFieldUnits = UnitUtils.getReferencedFieldUnits(fieldUnits, references);
        List<IContainerUnit> unreferencedFieldUnits = UnitUtils.getUnreferencedFieldUnits(fieldUnits, references);
        List<IRelationship> referencedRelationships = RelationshipUtils.getReferencedRelationships(relationships, references);
        List<IRelationship> unreferencedRelationships = RelationshipUtils.getUnreferencedRelationships(relationships, references);
        List<IContainerUnit> relationshipUnits = UnitUtils.buildRelationshipUnits(unreferencedRelationships, referencedRelationships,referencedFieldUnits);
        List<IContainerUnit> children = new ArrayList<IContainerUnit>();
        children.addAll(unreferencedFieldUnits);
        children.addAll(relationshipUnits);
        this.children = children;
    }




}
