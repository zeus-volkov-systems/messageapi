package gov.noaa.messageapi.interfaces;

import gov.noaa.messageapi.interfaces.IComponent;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.definitions.ContainerDefinition;

/**
 * A Container is a primary dimension of a Session. Containers
 * represent how schemas are factored into Collections,
 * Classifiers, and Transformations. Containers hold a definition and provide
 * the means of initializing themselves with possible cross-initialization
 * parameters coming from the other Session dimensions, Protocol and Schema.
 * @author Ryan Berkheimer
 */
public interface IContainer extends IComponent {

    /**
     * Initializes a container, making available the
     * protocol and schema.
     */
    public void initialize(IProtocol p, ISchema s);

    /**
     * Returns the ContainerDefinition associated with this Container.
     */
    public ContainerDefinition getDefinition();

}
