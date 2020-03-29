package gov.noaa.messageapi.interfaces;

import java.util.List;

//import gov.noaa.messageapi.interfaces.IPacket;
//import gov.noaa.messageapi.interfaces.IProtocolRecord;

/**
 * An IEndpoint is a user written class that is the terminating point of a given process.
 * Endpoints generally extend an AbstractEndpoint method, expose as much possible behavior
 * as configurable parameters in the constructor, and provide a list of fields
 * that will be used in creation of a new 'EndpointRecord'. When a Request is submitted,
 * the Response will eventually pass records into Endpoints, and call the Endpoint 'process' method.
 * Endpoints have access to lists of records defined in any container that was specified
 * in the Session Manifest as being part of a particular Endpoint connection. These records
 * can be retrieved within the 'process' method by making appropriate calls on the passed
 * ProtocolRecord. The process method returns an IPacket, which contains a list of IRecords and/or
 * IRejections, which will all eventually be recombined inside the calling IResponse.
 * @author Ryan Berkheimer
 */
public interface IEndpoint {

    /**
     * Process is the main method of an Endpoint. It is the method that
     * is called when an Endpoint is executed as part of a process.
     * Within a process method, the endpoint has complete access to any
     * record lists that were defined outside of code as part of the Endpoint
     * Connection specification in the Session manifest.
     * The process method must return an IPacket which contains IRecords and/or
     * IRejections to return to the caller.
     */
    public IPacket process(IProtocolRecord record);

    /**
     * Returns a list of fields used in the createRecord method of the Endpoint.
     * These fields may be used to define the records that are returned
     * to the caller in the IPacket.
     */
    public List<IField> getDefaultFields();

    /**
     * Creates a new Endpoint Record that can be used as a record for the
     * returned IPacket of the process method. This construct helps users
     * to understand what type of records will be returned by the Endpoint.
     */
    public IRecord createRecord();

}
