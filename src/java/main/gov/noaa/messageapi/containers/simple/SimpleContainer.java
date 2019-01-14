package gov.noaa.messageapi.containers.simple;

import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.containers.BaseContainer;

public class SimpleContainer extends BaseContainer implements IContainer {

    private static final Logger logger = LogManager.getLogger();

    public SimpleContainer(Map<String, Object> properties) {
        super(properties);
    }

    public SimpleContainer(IContainer container) {
        super(container);
    }

    public IContainer getCopy() {
        return new SimpleContainer(this);
    }

    public void initialize(IProtocol p, ISchema s) {
        try {
            this.createContainerDefinition(this.getProperties());
        } catch (Exception e) {
            logger.error("Could not create container definition.");
        }
    }

    public String getType() {
        return (String) this.definition.getMetadataMap().get("type");
    }

    public String getName() {
        return (String) this.definition.getMetadataMap().get("name");
    }

}
