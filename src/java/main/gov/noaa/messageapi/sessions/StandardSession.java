package gov.noaa.messageapi.sessions;

import java.util.Map;

import gov.noaa.messageapi.utils.general.JsonUtils;

import gov.noaa.messageapi.interfaces.ISession;

/**
 * The StandardSession allows users to ignore the system manifest and pass only
 * a fully qualified path to their parameter configuration. Once created, the
 * StandardSession should be used as an ISession.
 * 
 * @author Ryan Berkheimer
 */
public class StandardSession extends DefaultSession {

    final static String standardSessionName = "standard_session.json";
    final static String schemaMetadataName = "schema.json";
    final static String containerMetadataName = "container.json";
    final static String protocolMetadataName = "protocol.json";


    /**
     * Constructs a new publish session directly from a text map. The text map
     * should contain all the properties needed for Session Construction.
     * 
     * @param parameterSpec A text based map containing session construction
     *                      parameters
     * @throws Exception Throws exception if error creating session
     */
    public StandardSession(final String parameterSpec) throws Exception {
        super(buildStandardSession(parameterSpec));
    }

    /**
     * Accesses the installed template file using an env var, parses it into json,
     * and then updates targeted keys to 
     */
    private static ISession buildStandardSession(final String fqParamSpec) throws Exception {
        final String sessionTemplateDir = System.getenv("MESSAGEAPI_SESSION_TEMPLATE_DIR");
        final String sessionTemplateFQName = String.join("/", sessionTemplateDir, standardSessionName);
        final String schemaMetadataFQName = String.join("/", sessionTemplateDir, schemaMetadataName);
        final String containerMetadataFQName = String.join("/", sessionTemplateDir,
                containerMetadataName);
        final String protocolMetadataFQName = String.join("/", sessionTemplateDir, protocolMetadataName);
        final Map<String, Object> sessionMap = JsonUtils.convertObject(JsonUtils.parse(sessionTemplateFQName));
        StandardSession.modifyMapValue(sessionMap, "schema", "fields", fqParamSpec);
        StandardSession.modifyMapValue(sessionMap, "schema", "conditions", fqParamSpec);
        StandardSession.modifyMapValue(sessionMap, "schema", "metadata", schemaMetadataFQName);
        StandardSession.modifyMapValue(sessionMap, "container", "collections", fqParamSpec);
        StandardSession.modifyMapValue(sessionMap, "container", "transformations", fqParamSpec);
        StandardSession.modifyMapValue(sessionMap, "container", "metadata", containerMetadataFQName);
        StandardSession.modifyMapValue(sessionMap, "protocol", "endpoints", fqParamSpec);
        StandardSession.modifyMapValue(sessionMap, "protocol", "metadata", protocolMetadataFQName);
        return new DefaultSession(sessionMap);
    }

    @SuppressWarnings("unchecked")
    private static void modifyMapValue(final Map<String, Object> map, final String layer, final String component,
            final String newValue) {
        ((Map<String, Object>) ((Map<String, Object>) ((Map<String, Object>) map.get("constructor"))
                .get(layer)).get("constructor")).put(component, newValue);
    }


}
