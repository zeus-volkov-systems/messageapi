package gov.noaa.messageapi.records.container;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.utils.containers.RelationshipUtils;
import gov.noaa.messageapi.utils.containers.UnitUtils;

public class RelationshipUnit extends BaseUnit implements IContainerUnit {

    public RelationshipUnit(IRelationship relationship) {
        super("relationship");
        setRelationship(relationship);
    }

    public RelationshipUnit(IRelationship relationship, List<IRelationship> relationships,
                            List<IContainerUnit> fieldUnits) {
        super("relationship");
        setRelationship(relationship);
        setChildren(relationships, fieldUnits);
    }

    public RelationshipUnit getCopy(IRecord r) {
        return this;
    }

    private void setRelationship(IRelationship relationship) {
        this.relationship = relationship;
    }

    private void setChildren(List<IRelationship> relationships, List<IContainerUnit> fieldUnits) {
        List<IContainerUnit> children = new ArrayList<IContainerUnit>();
        List<String> references = RelationshipUtils.getReferences(this.relationship);
        List<IRelationship> childRelationships = RelationshipUtils.getReferencedRelationships(relationships, references);
        List<IContainerUnit> childFieldUnits = UnitUtils.getReferencedFieldUnits(fieldUnits, references);
        if (!childFieldUnits.isEmpty()) {
            children.addAll(childFieldUnits);
        }
        if (!childRelationships.isEmpty()) {
            List<IContainerUnit> childRelationshipUnits = childRelationships.stream().map(r -> {
                return new RelationshipUnit(r, relationships, fieldUnits);
            }).collect(Collectors.toList());
            children.addAll(childRelationshipUnits);
        }

    }


}
