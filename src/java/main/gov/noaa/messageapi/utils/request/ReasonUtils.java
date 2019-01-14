package gov.noaa.messageapi.utils.request;

import gov.noaa.messageapi.interfaces.IField;

/**
 * All methods in this class should be static utility methods that can
 * return or operate on Rejection reasons. Methods in this class should
 * be immutable and prefer parallelizable mechanisms where possible.
 */
public class ReasonUtils {

    /**
     * Creates a no-value rejection reason for the given field, writing which field
     * was missing a value.
     * @param  f The field for which a required value was missing
     * @return   A missing-required-field rejection reason statement
     */
    public static String getMissingRequiredFieldReason(IField f) {
        return new String(String.format("Required field %s was missing a value.", f.getName()));
    }

    /**
     * Creates an invalid-condition rejection reason. This is used in the case
     * where a record contains fields that did not satisfy the conditions.
     * @return An invalid-field-set rejection reason statement
     */
    public static String getInvalidFieldReason() {
        return new String("The record fields were invalidated against specified conditions.");
    }

}
