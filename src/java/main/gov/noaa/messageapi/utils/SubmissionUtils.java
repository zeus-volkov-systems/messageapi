package gov.noaa.messageapi.utils;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

import gov.noaa.messageapi.interfaces.ISubmission;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRecord;

import gov.noaa.messageapi.submissions.DefaultSubmission;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.request.SchemaUtils;
import gov.noaa.messageapi.utils.request.RejectionUtils;

public class SubmissionUtils {

    public static ISubmission create(ISchema schema, List<IRecord> records) {
        ISubmission submission = new DefaultSubmission();
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
