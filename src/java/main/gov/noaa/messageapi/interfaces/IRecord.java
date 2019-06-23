package gov.noaa.messageapi.interfaces;

import java.util.List;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * IRecords are the primary data type of
 * MessageAPI, holding collections (lists) of
 * IFields and IConditions. IRecords are typically
 * used in the context of an IRequest and then 
 * manipulated by the user through the API.
 * When used in this way, each IRecord gets its own copy of
 * every field and condition defined in the session manifest.
 * Record Fields and Conditions can then be given values in the
 * context of the Record. Lists of IRecords are the datatype
 * passed into and out of all Containers - and they are passed out
 * of every endpoint as part of a Packet (along with a list of Rejections).
 * @author Ryan Berkheimer
 */
public interface IRecord {

    /**
     * Returns the fields that are contained by the record
     */
    public List<IField> getFields();

    /**
     * Returns the conditions that are contained by the record
     */
    public List<ICondition> getConditions();

    /**
     * Returns a deep copy of the current state of the record
     */
    public IRecord getCopy();

    /**
     * Sets the field value in the record for the specified field.
     * The field is made an object so that multiple ways of field
     * reference are possible (i.e., field by name or field instance itself).
     */
    public void setField(Object field, Object value);

    /**
     * Returns the Field object with the given name/id as held by the
     * record.
     */
    public IField getField(String name);

    /**
     * Sets the entire fieldset for the record to the passed
     * list of fields.
     */
    public void setFields(List<IField> fields);

    /**
     * returns a true/false indicating whether the given field
     * (by id/name) exists in the record. While all records have
     * their fields defined outside of code, this method may be useful
     * for code-level inspection and/or automation.
     */
    public Boolean hasField(String fieldName);

    /**
     * Sets the given condition to hold the given value. The condition
     * is specified here as an object so that different ways of condition
     * reference may be used (e.g., by name/id or direct instance).
     */
    public void setCondition(Object condition, Object value);

    /**
     * Returns the condition attached to the record for the given ID.
     */
    public ICondition getCondition(String id);

    /**
     * Sets the entire condition set for the record to the passed list of conditions.
     */
    public void setConditions(List<ICondition> conditions);

    /**
     * Returns true/false whether the record is valid. The exact criteria for validity
     * is abstract, but could typically be used if all conditions are validated against
     * all fields.
     */
    public boolean isValid();

    /**
     * Sets the validity of the record to the passed true/false status.
     */
    public void setValid(boolean status);

}
