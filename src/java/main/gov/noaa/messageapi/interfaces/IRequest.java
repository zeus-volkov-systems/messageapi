package gov.noaa.messageapi.interfaces;

import java.util.List;

//import gov.noaa.messageapi.interfaces.IResponse;
//import gov.noaa.messageapi.interfaces.IRecord;

/**
 * A Request is the primary method of communicating process
 * streams or batches in MessageAPI. Requests are derived directly from
 * Sessions, which serve as templates for Requests. Requests themselves
 * hold sets of Records, along with a copy of the Schema, Container,
 * and Protocol used in Request construction. Requests also contain a
 * singular Request-wide Request Record, which hold request wide conditions.
 * Using the setCondition method on an IRequest will set the value of the
 * referenced condition in the request record.
 * 
 * Requests should be executed using the submit() method. The submit() method
 * in the DefaultRequest immediately returns a new Response object,
 * executes asynchronously, and eventually resolves in the response.
 * 
 * Requests may be reused by updating their record sets and again calling submit().
 * This manner of use will maintain any state in the request.
 * Creating new requests from a session will create entirely new request state.
 * 
 * @author Ryan Berkheimer
 */
public interface IRequest {

    /**
     * Creates and returns a new record for the request. The record
     * structure is outlayed entirely outside of code,
     * in the session manifest.
     */
    public IRecord createRecord();

    /**
     * Creates and returns a deep copy of the request.
     * All parts of the request are copied (e.g., protocol, schema, container,
     * record defs).
     */
    public IRequest getCopy();

    /**
     * Creates an returns a copy of the request, while only copying
     * the parts of a request specified by name keyword in the argument list.
     * Which specific deep-copy elements are available should be checked against
     * the implementing Request class.
     */
    public IRequest getCopy(List<String> copyComponents);

    /**
     * Returns the type of the request as a string. This is useful
     * for tracking metadata or in-code inspection of implementing class
     * type. The type of request is usually set as a static variable
     * in the implementing class.
     */
    public String getType();

    /**
     * Returns the Container held by the Request.
     */
    public IContainer getContainer();

    /**
     * Returns the Schema held by the request.
     */
    public ISchema getSchema();

    /**
     * Returns the Protocol held by the request.
     */
    public IProtocol getProtocol();

    /**
     * Returns the Records currently held by the request.
     */
    public List<IRecord> getRecords();

    /**
     * Returns the request-wide record held by the request.
     * This record is used by request-wide conditions.
     */
    public IRecord getRequestRecord();

    /**
     * Sets a condition value for the specified condition
     * on the request-record.
     */
    public void setCondition(String id, Object value);

    /**
     * Sets the records on the request to the provided list of records.
     * (Does not append, just replaces).
     */
    public void setRecords(List<IRecord> records);

    /**
     * Submits the request for processing, immediately returning a response.
     */
    public IResponse submit();

}
