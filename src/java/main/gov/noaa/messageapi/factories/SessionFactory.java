package gov.noaa.messageapi.factories;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.parsers.plugins.SessionPluginParser;

/**
 * Creates a new session from a configured specification. The specification
 * should conform to the domain model laid out in the documentation and examples.
 * This specification bootstraps required classes at runtime and creates a reusable
 * topology for fast request creation.
 * @author Ryan Berkheimer
 */
public class SessionFactory {

    /**
     * Creates a new session from a specified configuration as a path to a json map.
     * @param  spec      The path to the configuration map
     * @return           A new Session object
     * @throws Exception In the case that parsing or bootstrapping fails
     */
    public static ISession create(String spec) throws Exception {
         return (ISession) new SessionPluginParser(spec).build();
    }

}
