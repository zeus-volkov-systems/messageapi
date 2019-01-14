package gov.noaa.messageapi.utils.protocol.jdbc;


public class JdbcUrlPatternLookup {

    public static String getUrlPattern(String container) {
        switch(container) {
            case "sqllite":
                return "jdbc:sqlite:{database}";
        }
        return null;
    }
}
