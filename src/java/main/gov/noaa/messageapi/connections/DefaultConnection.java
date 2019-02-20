package gov.noaa.messageapi.connections;

import java.util.List;
import java.util.Map;

public class DefaultConnection {

    private String id;
    private List<String> bins;

    @SuppressWarnings("unchecked")
    public DefaultConnection(Map<String,Object> connectionMap) throws Exception {
        setId((String) connectionMap.get("id"));
        setBins((List<String>) connectionMap.get("bins"));
    }

    public String getId() {
        return this.id;
    }

    public List<String> getBins() {
        return this.bins;
    }

    private void setId(String id) {
        this.id = id;
    }

    private void setBins(List<String> bins) {
        this.bins = bins;
    }
}
