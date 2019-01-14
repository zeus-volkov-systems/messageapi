package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.requests.AddRequest;
import gov.noaa.messageapi.requests.GetRequest;
import gov.noaa.messageapi.requests.RemoveRequest;
import gov.noaa.messageapi.requests.UpdateRequest;

/**
 * Returns a new request based on a specified type. Supports
 * add, get, remove, update requests. The request that is created is
 * created as a standalone copy, with its own copy of the session schema,
 * container, and protocol as they existed at the time of request formation.
 * This ensures that if a session parameter changes, the request will not be
 * altered by that change in subsequent use, making it threadsafe against
 * changes in session definitions.
 */
public class RequestFactory {

    /**
     * Creates a new request based on the desired type and a session topology set
     * of schema, container, and protocol.
     * @param  type      The type of request to create
     * @param  schema    The schema to use in this request
     * @param  container The container to use in this request
     * @param  protocol  The protocol to use in this request
     * @return           A new request
     */
    public static IRequest create(String type,
        ISchema schema, IContainer container, IProtocol protocol) {
        switch(type) {
            case "add":
                return new AddRequest(schema, container, protocol);
            case "get":
                return new GetRequest(schema, container, protocol);
            case "remove":
                return new RemoveRequest(schema, container, protocol);
            case "update":
                return new UpdateRequest(schema, container, protocol);
        }
        return null;
    }
}
