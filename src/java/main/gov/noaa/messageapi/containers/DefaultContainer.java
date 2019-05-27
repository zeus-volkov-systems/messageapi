package gov.noaa.messageapi.containers;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;

import gov.noaa.messageapi.containers.BaseContainer;
import gov.noaa.messageapi.metadata.DefaultMetadata;

/**
 * @author Ryan Berkheimer
 */
public class DefaultContainer extends BaseContainer implements IContainer {

    public DefaultContainer(Map<String, Object> properties) {
        super(properties);
    }

    public DefaultContainer(IContainer container) {
        super(container);
        this.setMetadata(container.getDefinition().getMetadataMap());
    }

    public IContainer getCopy() {
        return new DefaultContainer(this);
    }

    public void initialize(IProtocol p, ISchema s) {
        try {
            this.createContainerDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
        } catch (Exception e) {}
    }

    public String getType() {
        return "DefaultContainer";
    }

    private void setMetadata(Map<String,Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

}
