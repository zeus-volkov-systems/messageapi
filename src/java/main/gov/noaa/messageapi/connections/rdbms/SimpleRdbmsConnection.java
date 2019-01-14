package gov.noaa.messageapi.connections.rdbms;

import java.util.Map;

import gov.noaa.messageapi.connections.BaseConnection;

public class SimpleRdbmsConnection extends BaseConnection {

    private String url;
    private String user;
    private String password;

    public SimpleRdbmsConnection(Map<String,Object> connectionMap) throws Exception {
        super(connectionMap);
        setUrl((String) connectionMap.get("url"));
        setUser((String) connectionMap.get("user"));
        setPassword((String) connectionMap.get("password"));
    }

    private void setUrl(String url) {
        this.url = url;
    }

    private void setUser(String user) {
        this.user = user;
    }

    private void setPassword(String password) {
        this.password = password;
    }

    public String getUrl() {
        return this.url;
    }

    public String getUser() {
        return this.user;
    }

    public String getPassword() {
        return this.password;
    }

}
