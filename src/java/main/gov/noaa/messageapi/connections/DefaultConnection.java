package gov.noaa.messageapi.connections;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IContainerRecord;


public class DefaultConnection extends BaseConnection implements IConnection {

    private String id;
    private List<String> bins;

    @SuppressWarnings("unchecked")
    public DefaultConnection(String endpointClass, Map<String,Object> connectionMap) throws Exception {
        super(endpointClass, (Map<String,Object>) connectionMap.get("parameters"));
        setId((String) connectionMap.get("id"));
        setBins(connectionMap.get("bins"));
    }

    public String getId() {
        return this.id;
    }

    public List<String> getBins() {
        return this.bins;
    }

    public IProtocolRecord process(List<IContainerRecord> containerRecords) {
        return this.getEndpoint().process(containerRecords);
    }

    private void setId(String id) {
        this.id = id;
    }

    @SuppressWarnings("unchecked")
    private void setBins(Object bins) {
        if (bins instanceof String) {
            this.bins = new ArrayList<String>();
            this.bins.add((String) bins);
        } else if (bins instanceof List) {
            this.bins = (List<String>) bins;
        }
    }
}
