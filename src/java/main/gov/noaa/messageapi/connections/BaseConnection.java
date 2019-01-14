package gov.noaa.messageapi.connections;

import java.util.Map;

public class BaseConnection {

    private String name;

    public BaseConnection(Map<String,Object> connectionMap) throws Exception {
        setName((String) connectionMap.get("name"));
    }

    private void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

}
