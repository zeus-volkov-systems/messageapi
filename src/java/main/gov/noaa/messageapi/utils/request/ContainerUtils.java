package gov.noaa.messageapi.utils.request;

import gov.noaa.messageapi.utils.containers.UnitUtils;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.interfaces.IRelationship;
import gov.noaa.messageapi.records.container.RootUnit;
import gov.noaa.messageapi.utils.containers.RelationshipUtils;

public class ContainerUtils {

    public static List<IContainerUnit> getContainers(IContainer container, List<IRecord> records) {
        IContainerUnit recordBlueprint = getBlueprint(container);
        return records.stream().map(r -> {
            return recordBlueprint.getCopy(r);
        }).collect(Collectors.toList());
    }

    public static IContainerUnit getBlueprint(IContainer container) {
        List<IContainerUnit> fieldUnits = UnitUtils.buildFieldUnits(container.getDefinition().getContainerMaps());
        List<IRelationship> relationships = RelationshipUtils.buildRelationships(container.getDefinition().getRelationshipMaps());
        return new RootUnit(fieldUnits, relationships);
    }

}
