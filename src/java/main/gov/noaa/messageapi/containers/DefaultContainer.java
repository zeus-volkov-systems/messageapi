package gov.noaa.messageapi.containers;

import java.util.Map;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.containers.BaseContainer;

public class DefaultContainer extends BaseContainer implements IContainer {

    public DefaultContainer(Map<String, Object> properties) {
        super(properties);
    }

    public DefaultContainer(IContainer container) {
        super(container);
    }

    public IContainer getCopy() {
        return new DefaultContainer(this);
    }

    public void initialize(IProtocol p, ISchema s) {
        try {
            this.createContainerDefinition(this.getProperties());
        } catch (Exception e) {}
    }

    public String getType() {
        return (String) this.definition.getMetadataMap().get("type");
    }

    public String getName() {
        return (String) this.definition.getMetadataMap().get("name");
    }

}
