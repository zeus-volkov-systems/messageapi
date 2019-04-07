package gov.noaa.messageapi.utils.request;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRecord;

import gov.noaa.messageapi.packets.DefaultPacket;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.request.SchemaUtils;
import gov.noaa.messageapi.utils.request.RejectionUtils;

public class PacketUtils {

    public static IPacket create(ISchema schema, List<IRecord> records) {
        IPacket submission = new DefaultPacket();
        List<IRejection> primaryRejections = RejectionUtils.getRequiredFieldRejections(records);
        List<IRecord> filteredRecords = SchemaUtils.filterFieldlessConditions(
                                         SchemaUtils.filterNonValuedConditions(
                                          SchemaUtils.filterNonValuedFields(
                                           SchemaUtils.filterRejections(records, primaryRejections))));
        List<IRejection> secondaryRejections = RejectionUtils.getFieldConditionRejections(schema, filteredRecords);
        submission.setRecords(SchemaUtils.filterRejections(filteredRecords, secondaryRejections));
        submission.setRejections(ListUtils.flatten(new ArrayList<List<IRejection>>(Arrays.asList(primaryRejections, secondaryRejections))));
        return submission;
    }

}
