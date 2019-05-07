package gov.noaa.messageapi.protocols;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IConnection;

import gov.noaa.messageapi.protocols.BaseProtocol;
import gov.noaa.messageapi.metadata.DefaultMetadata;
import gov.noaa.messageapi.connections.DefaultConnection;

import gov.noaa.messageapi.utils.general.ListUtils;

/**
 * The default protocol handles protocols that consist of an endpoint class
 * capable of producing objects, and
 */
public class DefaultProtocol extends BaseProtocol implements IProtocol {

    List<IConnection> connections = null;

    public DefaultProtocol(Map<String, Object> protocolMap) {
        super(protocolMap);
    }

    public DefaultProtocol(IProtocol protocol) throws Exception {
        super(protocol);
        this.setMetadata(protocol.getDefinition().getMetadataMap());
        this.setConnections(protocol.getDefinition().getEndpointMap());
    }

    public IProtocol getCopy() {
        try {
            return new DefaultProtocol(this);
        } catch (Exception e) {
            return null;
        }
    }

    public void initialize(IContainer c, ISchema s) {
        try {
            this.createProtocolDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
            this.setConnections(this.definition.getEndpointMap());
        } catch (Exception e) {}
    }

    public List<IConnection> getConnections() {
        return this.connections;
    }

    public String getType() {
        return "DefaultProtocol";
    }

    private void setMetadata(Map<String,Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

    private void setConnections(Map<String, List<Map<String,Object>>> endpointMap) throws Exception {
        this.connections = ListUtils.flatten(endpointMap.entrySet().stream().map(entry -> {
            String plugin = entry.getKey();
            return ListUtils.removeAllNulls(entry.getValue().stream().map(connectionMap -> {
                try {
                    return (IConnection) new DefaultConnection(plugin, (Map<String,Object>) connectionMap);
                } catch (Exception e) {
                    return null;
                }
            }).collect(Collectors.toList()));
        }).collect(Collectors.toList()));
    }

}
