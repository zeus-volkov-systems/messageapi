package gov.noaa.messageapi.utils.request;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRecord;

import gov.noaa.messageapi.packets.DefaultPacket;

import gov.noaa.messageapi.utils.general.ListUtils;


/**
 * This class contains static utilities related to creating, parsing, routing, or otherwise
 * manipulating Packets. Packets are containers that hold records and rejections and are
 * the return type of endpoints. 
 * @author Ryan Berkheimer
 */
public class PacketUtils {

    public static IPacket create(final ISchema schema, final List<IRecord> records) {
        final IPacket dataPacket = new DefaultPacket();
        final List<IRejection> primaryRejections = RejectionUtils.getRequiredFieldRejections(records);
        final List<IRecord> filteredRecords = SchemaUtils.filterFieldlessConditions(
                SchemaUtils.filterNonValuedConditions(SchemaUtils.filterRejections(records, primaryRejections)));
        final List<IRejection> secondaryRejections = RejectionUtils.getFieldConditionRejections(schema,
                filteredRecords);
        dataPacket.setRecords(SchemaUtils.filterRejections(filteredRecords, secondaryRejections));
        dataPacket.setRejections(ListUtils
                .flatten(new ArrayList<List<IRejection>>(Arrays.asList(primaryRejections, secondaryRejections))));
        return dataPacket;
    }

    public static IPacket createInParallel(final ISchema schema, final List<IRecord> records) {
        final IPacket dataPacket = new DefaultPacket();
        final List<IRejection> primaryRejections = RejectionUtils.getRequiredFieldRejectionsInParallel(records);
        final List<IRecord> filteredRecords = SchemaUtils.filterFieldlessConditionsInParallel(
                SchemaUtils.filterNonValuedConditionsInParallel(SchemaUtils.filterRejectionsInParallel(records, primaryRejections)));
        final List<IRejection> secondaryRejections = RejectionUtils.getFieldConditionRejectionsInParallel(schema,
                filteredRecords);
        dataPacket.setRecords(SchemaUtils.filterRejectionsInParallel(filteredRecords, secondaryRejections));
        dataPacket.setRejections(ListUtils
                .flatten(new ArrayList<List<IRejection>>(Arrays.asList(primaryRejections, secondaryRejections))));
        return dataPacket;
    }

    public static IPacket combineResults(final List<IPacket> packets) {
        final List<IRecord> allRecords = ListUtils
                .flatten(packets.stream().map(packet -> packet.getRecords()).collect(Collectors.toList()));
        final List<IRejection> allRejections = ListUtils
                .flatten(packets.stream().map(packet -> packet.getRejections()).collect(Collectors.toList()));
        return new DefaultPacket(allRecords, allRejections);
    }

}
