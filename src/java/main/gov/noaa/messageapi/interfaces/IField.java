package gov.noaa.messageapi.interfaces;

/**
 * The IField is a fundamental, value-oriented
 * unit in MessageAPI. IFields are defined outside of code
 * in a session spec and must have a globally unique id for that session.
 * Id and Name are the same parameter. The type of the IField describes
 * what type the value is and is used in validation, routing, and optimization.
 * As values can be any type of object, types are required to help the system
 * with typing. 
 * @author Ryan Berkheimer
 */
public interface IField {

    /**
     * Returns the ID of the field. 
     * IDs must be globally unique in
     * the context of a session.
     */
    public String getId();
    /**
     * Returns the same thing as getId.
     * Will be deprecated in an upcoming release.
     */
    public String getName();

    /**
     * Returns the type of the field (i.e., 'string', 'integer',
     * or some user defined object like 'cat').
     */
    public String getType();

    /**
     * Used contextually to determine whether
     * or not this field is required for subsequent processing.
     */
    public boolean isRequired();

    /**
     * Used contextually to determine whether or not
     * this field is valid. This could be used in type validation
     * or some other way.
     */
    public boolean isValid();

    /**
     * Returns the value of the field.
     * Any type that is valid in Java is valid here.
     */
    public Object getValue();

    /**
     * sets the value of the field.
     */
    public void setValue(Object value);

    /**
     * Sets true or false whether or not the field is
     * valid against some generalized criteria
     */
    public void setValid(Boolean valid);

    /**
     * Allows setting of the type of the field as a string.
     */
    public void setType(String type);

}
