package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.records.container.FieldUnit;
import gov.noaa.messageapi.records.container.RelationshipUnit;

public class UnitUtils {

    public static List<IContainerUnit> buildFieldUnits(List<Map<String,Object>> fieldContainerMaps) {
        return fieldContainerMaps.stream().map(m -> {
            return new FieldUnit(m);
        }).collect(Collectors.toList());
    }

    public static List<IContainerUnit> buildRelationshipUnits(List<IRelationship> relationships,
                                            List<IRelationship> childRelationships,
                                            List<IContainerUnit> childFieldUnits) {
            return relationships.stream()
                    .map(r -> new RelationshipUnit(r, childRelationships, childFieldUnits))
                    .collect(Collectors.toList());
    }

    public static List<IContainerUnit> getReferencedFieldUnits(List<IContainerUnit> fieldUnits, List<String> referencedNames) {
        return fieldUnits.stream().filter(fieldUnit -> {
            if (referencedNames.contains(fieldUnit.getName())) {
                return true;
            }
            return false;
        }).collect(Collectors.toList());
    }

    public static List<IContainerUnit> getUnreferencedFieldUnits(List<IContainerUnit> fieldUnits, List<String> referencedNames) {
        return fieldUnits.stream().filter(fieldUnit -> {
            if (referencedNames.contains(fieldUnit.getName())) {
                return false;
            }
            return true;
        }).collect(Collectors.toList());
    }


}
