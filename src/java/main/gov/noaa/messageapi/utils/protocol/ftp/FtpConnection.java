package gov.noaa.messageapi.utils.protocol.ftp;

/*import gov.noaa.taskapi.services.LogService;

import gov.noaa.ncei.asos.ingest.utils.ResourceUtils;
import gov.noaa.messageapi.api.ISession;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;*/

public class FtpConnection {

    /*public static void connect(ISession session) throws Exception {
        Connection conn = null;
        try {
            Class.forName("org.sqlite.JDBC");
            conn = DriverManager.getConnection((String) session.get("url"));
            session.set("connection", conn);
        } catch (SQLException e) {
            LogService.error(String.format("Could not connect to database %s. Error: %s", session.get("database"),e.getMessage()));
        }
    }

    public static void disconnect(ISession session) {
        Connection conn = null;
        try {
            conn = (Connection) session.get("connection");
        } finally {
            if (conn != null) {
                    ResourceUtils.safeCloseSqlConn(conn);
                    session.set("connection", null);
            }
        }
    }*/
}
