package gov.noaa.messageapi.sessions;

import static java.lang.String.join;

import java.io.File;
import java.util.Map;

import gov.noaa.messageapi.exceptions.MessageApiException;

import gov.noaa.messageapi.utils.general.JsonUtils;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.ISession;

/**
 * The SequentialSession allows users to ignore the system manifest and pass only
 * a fully qualified path to their parameter configuration. Once created, the
 * StandardSession should be used as an ISession.
 * 
 * @author Ryan Berkheimer
 */
public class SequentialSession extends DefaultSession {

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
    public SequentialSession(final String parameterSpec) throws Exception {
        super(SequentialSession.buildSequentialSession(parameterSpec));
    }

    @Override
    public IRequest createRequest() {
        return new SequentialRequest(this.getSchema(), this.getContainer(), this.getProtocol());
    }

    /**
     * Accesses the installed template file using an env var, parses it into json,
     * and then updates targeted keys to
     */
    private static ISession buildStandardSession(final String fqParamSpec) throws Exception {
        final Map<String, Object> parameterMap = StandardSession.parseParameterMap(fqParamSpec);
        final String sessionTemplateDir = System.getenv("MESSAGEAPI_SESSION_TEMPLATE_DIR");
        final String sessionTemplateFQName = String.join(File.separator, sessionTemplateDir, standardSessionName);
        final Map<String, Object> sessionMap = StandardSession.parseSessionMap(sessionTemplateFQName);
        final String schemaMetadataFQName = String.join(File.separator, sessionTemplateDir, schemaMetadataName);
        final String containerMetadataFQName = join(File.separator, sessionTemplateDir, containerMetadataName);
        final String protocolMetadataFQName = String.join(File.separator, sessionTemplateDir, protocolMetadataName);
        if (parameterMap.containsKey("fields")) {
            StandardSession.setMapValue(sessionMap, "schema", "fields", fqParamSpec);
        } else {
            throw new MessageApiException(StandardSession.getMissingKeyErrorMessage("fields"));
        }
        if (parameterMap.containsKey("collections")) {
            StandardSession.setMapValue(sessionMap, "container", "collections", fqParamSpec);
        } else {
            throw new MessageApiException(StandardSession.getMissingKeyErrorMessage("collections"));
        }
        if (parameterMap.containsKey("endpoints")) {
            StandardSession.setMapValue(sessionMap, "protocol", "endpoints", fqParamSpec);
        } else {
            throw new MessageApiException(StandardSession.getMissingKeyErrorMessage("endpoints"));
        }
        if (parameterMap.containsKey("conditions")) {
            StandardSession.setMapValue(sessionMap, "schema", "conditions", fqParamSpec);
        } else {
            StandardSession.removeMapKey(sessionMap, "schema", "conditions");
        }
        if (parameterMap.containsKey("transformations")) {
            StandardSession.setMapValue(sessionMap, "container", "transformations", fqParamSpec);
        } else {
            StandardSession.removeMapKey(sessionMap, "container", "transformations");
        }
        StandardSession.setMapValue(sessionMap, "schema", "metadata", schemaMetadataFQName);
        StandardSession.setMapValue(sessionMap, "container", "metadata", containerMetadataFQName);
        StandardSession.setMapValue(sessionMap, "protocol", "metadata", protocolMetadataFQName);
        return new DefaultSession(sessionMap);
    }

    /**
     * Parses the session map and checks for installation errors.
     */
    private static Map<String, Object> parseSessionMap(String sessionTemplateFQName) throws Exception {
        try {
            return JsonUtils.convertObject(JsonUtils.parse(sessionTemplateFQName));
        } catch (Exception e) {
            throw new MessageApiException("Failed trying to parse the standard session. Check your MessageAPI installation.");
        }
    }

    /**
     * Parses the parameter map and checks for configuration errors.
     */
    private static Map<String, Object> parseParameterMap(String fqParamSpec) throws Exception {
        try {
            return JsonUtils.convertObject(JsonUtils.parse(fqParamSpec));
        } catch (Exception e) {
            throw new MessageApiException("Failed initial configuration parsing check. Double check your JSON structure.");
        }
    }

    /**
     * Sets a map value for a key on a layer (e.g., schema/container/protocol and a component)
     */
    @SuppressWarnings("unchecked")
    private static void setMapValue(final Map<String, Object> map, final String layer, final String component,
            final String newValue) {
        ((Map<String, Object>) ((Map<String, Object>) ((Map<String, Object>) map.get("constructor")).get(layer))
                .get("constructor")).put(component, newValue);
    }

    /**
     * Removes a component map key attached to a given layer
     */
    @SuppressWarnings("unchecked")
    private static void removeMapKey(final Map<String, Object> map, final String layer, final String component) {
        ((Map<String, Object>) ((Map<String, Object>) ((Map<String, Object>) map.get("constructor")).get(layer))
                .get("constructor")).keySet().remove(component);
    }

    /**
     * Builds a missing required parameter key error message for the specified component.
     */
    private static String getMissingKeyErrorMessage(final String key) {
        return String.format("Your parameter map is missing the required '%s' key. Check your configuration. Stopping session building now.", key);
    }

}
