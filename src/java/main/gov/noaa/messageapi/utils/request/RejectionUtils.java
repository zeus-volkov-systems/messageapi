package gov.noaa.messageapi.utils.request;

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.rejections.DefaultRejection;
import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.schema.FieldUtils;
import gov.noaa.messageapi.utils.schema.ConditionUtils;

/**
 * All methods in this class should be static utility methods that can
 * be reused by various request types. All public methods included in this utilities
 * module should perform immutable operations on arguments and return a rejection
 * or rejection-collection.
 * @author Ryan Berkheimer
 */
public class RejectionUtils {

    /**
     * Creates a new list of rejections for the given input record set.
     * @param  records Records to analyze/determine rejections
     * @return         A list of rejections created for the input records.
     */
    public static List<IRejection> getRequiredFieldRejections (final List<IRecord> records) {
        final List<IRejection> rejections = records.stream().map(r -> {
            final List<String> reasons = r.getFields().stream().map(f -> {
                if (!FieldUtils.validateRequired(f)) {
                    return ReasonUtils.getMissingRequiredFieldReason(f);
                }
                return null;
            }).collect(Collectors.toList());
            if (!ListUtils.isAllNulls(reasons)) {
                return new DefaultRejection(r, ListUtils.removeAllNulls(reasons));
            }
            return null;
        }).collect(Collectors.toList());
        if (!ListUtils.isAllNulls(rejections)) {
            return ListUtils.removeAllNulls(rejections);
        }
        return new ArrayList<IRejection>();
    }

    /**
     * Creates a new list of rejections for the given input record set.
     * 
     * @param records Records to analyze/determine rejections
     * @return A list of rejections created for the input records.
     */
    public static List<IRejection> getRequiredFieldRejectionsInParallel(final List<IRecord> records) {
        final List<IRejection> rejections = records.parallelStream().map(r -> {
            final List<String> reasons = r.getFields().parallelStream().map(f -> {
                if (!FieldUtils.validateRequired(f)) {
                    return ReasonUtils.getMissingRequiredFieldReason(f);
                }
                return null;
            }).collect(Collectors.toList());
            if (!ListUtils.isAllNulls(reasons)) {
                return new DefaultRejection(r, ListUtils.removeAllNulls(reasons));
            }
            return null;
        }).collect(Collectors.toList());
        if (!ListUtils.isAllNulls(rejections)) {
            return ListUtils.removeAllNulls(rejections);
        }
        return new ArrayList<IRejection>();
    }

    /**
     * Return a list of rejections for a given record list by looking at each record
     * individually, comparing the field values to conditions, and creating a
     * rejection for any record with field values that do not meet the conditions.
     * 
     * @param schema  A schema holding the comparison operator factory
     * @param records A list of record to use for rejection assembly
     * @return A list of rejections based on invalid records
     */
    public static List<IRejection> getFieldConditionRejections(final ISchema schema, final List<IRecord> records) {
        final List<IRejection> rejections = records.stream().map(r -> {
            if (!FieldUtils.validateConditions(schema, r, ConditionUtils.getTopLevelConditions(r))) {
                final String reason = ReasonUtils.getInvalidFieldReason();
                return new DefaultRejection(r, reason);
            }
            return null;
        }).collect(Collectors.toList());
        if (!ListUtils.isAllNulls(rejections)) {
            return ListUtils.removeAllNulls(rejections);
        }
        return new ArrayList<IRejection>();
    }

    /**
     * Return a list of rejections for a given record list by looking at each record
     * individually, comparing the field values to conditions, and creating a
     * rejection for any record with field values that do not meet the conditions.
     * 
     * @param schema  A schema holding the comparison operator factory
     * @param records A list of record to use for rejection assembly
     * @return A list of rejections based on invalid records
     */
    public static List<IRejection> getFieldConditionRejectionsInParallel(final ISchema schema, final List<IRecord> records) {
        final List<IRejection> rejections = records.parallelStream().map(r -> {
            if (!FieldUtils.validateConditions(schema, r, ConditionUtils.getTopLevelConditions(r))) {
                final String reason = ReasonUtils.getInvalidFieldReason();
                return new DefaultRejection(r, reason);
            }
            return null;
        }).collect(Collectors.toList());
        if (!ListUtils.isAllNulls(rejections)) {
            return ListUtils.removeAllNulls(rejections);
        }
        return new ArrayList<IRejection>();
    }


}
