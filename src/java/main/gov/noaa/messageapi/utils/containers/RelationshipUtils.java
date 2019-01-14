package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.relationships.simple.SimpleRelationship;
import gov.noaa.messageapi.utils.general.ListUtils;

public class RelationshipUtils {

    public static List<IRelationship> buildRelationships(List<Map<String,Object>> relationshipMaps) {
        return relationshipMaps.stream().map(r -> {
            return new SimpleRelationship(r);
        }).collect(Collectors.toList());
    }

    public static List<String> getReferences(List<IRelationship> relationships) {
        return ListUtils.flatten(relationships.stream().map(r -> {
            List<String> relationshipReferences = new ArrayList<String>();
            relationshipReferences.add(r.getParent());
            relationshipReferences.add(r.getChild());
            return relationshipReferences;
        }).collect(Collectors.toList()));
    }

    public static List<String> getReferences(IRelationship relationship) {
        List<String> relationshipReferences = new ArrayList<String>();
        relationshipReferences.add(relationship.getParent());
        relationshipReferences.add(relationship.getChild());
        return relationshipReferences;
    }

    public static List<IRelationship> getReferencedRelationships(List<IRelationship> relationships, List<String> referencedNames) {
        return relationships.stream().filter(relationship -> {
            if (referencedNames.contains(relationship.getId())) {
                return true;
            }
            return false;
        }).collect(Collectors.toList());
    }

    public static List<IRelationship> getUnreferencedRelationships(List<IRelationship> relationships, List<String> referencedNames) {
        return relationships.stream().filter(relationship -> {
            if (referencedNames.contains(relationship.getId())) {
                return false;
            }
            return true;
        }).collect(Collectors.toList());
    }

}
