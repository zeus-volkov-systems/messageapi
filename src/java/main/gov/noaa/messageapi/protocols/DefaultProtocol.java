package gov.noaa.messageapi.protocols;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.protocols.BaseProtocol;
import gov.noaa.messageapi.metadata.DefaultMetadata;

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
        this.setConnections(protocol.getDefinition().getEndpoint(), protocol.getDefinition().getConnectionMaps());
    }

    public IProtocol getCopy() {
        try {
            return new DefaultProtocol(this);
        } catch (Exception e) {
            return null;
        }
    }

    public void initialize(IContainer c, ISchema s){
        try {
            this.createProtocolDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
            this.setConnections(this.definition.getEndpoint(), this.definition.getConnectionMaps());
        } catch (Exception e) {}
    }

    public void process(List<IContainerRecord> containerRecords) {
        for(IConnection c: this.connections) {
            c.process(containerRecords);
        }
    }

    public String getType() {
        return "DefaultProtocol";
    }

    private void setMetadata(Map<String,Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

    @SuppressWarnings("unchecked")
    private void setConnections(String endpoint, List<Map<String,Object>> connectionMaps) throws Exception {
        this.connections = ListUtils.removeAllNulls(connectionMaps.stream().map(connectionMap -> {
            try {
                return initializeConnection(endpoint, (Map<String,Object>) connectionMap.get("parameters"));
            } catch (Exception e) {
                return null;
            }
        }).collect(Collectors.toList()));
    }



}
