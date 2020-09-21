package gov.noaa.messageapi.utils.request;

import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.interfaces.IRejection;

import gov.noaa.messageapi.utils.schema.FieldUtils;
import gov.noaa.messageapi.utils.schema.ConditionUtils;

/**
 * This class contains static utilities for parsing or manipulating a session schema layer
 * and schema layer components such as records, fields, and conditions.
 * All methods in this class should be static utility methods that can
 * be reused by various request types. All public methods included in this utilities
 * module should perform immutable operations on arguments and return a record
 * or record-collection.
 * @author Ryan Berkheimer
 */
public class SchemaUtils {

    /**
     * Returns a new list of IRecords based on the passed IRecord list with those IRecords
     * that are also contained in the rejections removed.
     * @param  records    A list of Records to filter
     * @param  rejections A list of rejections to filter from the Records
     * @return            A new list of records minus the rejections
     */
    public static List<IRecord> filterRejections(final List<IRecord> records, final List<IRejection> rejections) {
        if (rejections != null) {
            final List<IRecord> rejectedRecords = rejections.stream().map(r -> {
                return r.getRecord();
            }).collect(Collectors.toList());
            final List<IRecord> filteredRecords = records.stream().filter(r -> !rejectedRecords.contains(r))
                    .collect(Collectors.toList());
            return filteredRecords;
        }
        return records;
    }

    /**
     * Returns a new list of IRecords based on the passed IRecord list with all
     * non-valued fields (fields without values) removed from each record.
     * 
     * @param records The list of records to process
     * @return A list of new IRecords with non-valued fields removed.
     */
    public static List<IRecord> filterNonValuedFields(final List<IRecord> records) {
        return records.stream().map(r -> {
            final List<IField> fields = FieldUtils.filterNonValuedFields(r.getFields());
            final IRecord newR = r.getCopy();
            newR.setFields(fields);
            return newR;
        }).collect(Collectors.toList());
    }

    /**
     * Returns a new list of IRecords based on the passed IRecord list with all
     * non-valued conditions (conditions without values) removed from each record.
     * 
     * @param records The list of records to process
     * @return A list of new IRecords with non-valued conditions removed.
     */
    public static List<IRecord> filterNonValuedConditions(final List<IRecord> records) {
        return records.stream().map(r -> {
            final List<ICondition> conditions = ConditionUtils.filterNonValuedConditions(r.getConditions());
            // IRecord newR = r.getCopy();
            // newR.setConditions(conditions);
            r.setConditions(conditions);
            // return newR;
            return r;
        }).collect(Collectors.toList());
    }

    /**
     * Returns a new list of IRecords based on the passed IRecord list with all
     * fieldless conditions (conditions corresponding to a non-existent record
     * field) removed from the record.
     * 
     * @param records The list of records to process
     * @return A list of new IRecords with fieldless conditions removed.
     */
    public static List<IRecord> filterFieldlessConditions(final List<IRecord> records) {
        return records.stream().map(r -> {
            final List<ICondition> conditions = ConditionUtils.filterFieldlessConditions(r);
            final IRecord newR = r.getCopy();
            newR.setConditions(conditions);
            return newR;
        }).collect(Collectors.toList());
    }


}
