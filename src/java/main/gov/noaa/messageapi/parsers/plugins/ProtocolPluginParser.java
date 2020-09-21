package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IPluginParser;

/**
 * This class builds the protocol plugin from the session spec.
 * @author Ryan Berkheimer
 */
public class ProtocolPluginParser extends BasePluginParser implements IPluginParser {

    public ProtocolPluginParser(final Object protocolMap) throws Exception {
        super(protocolMap);
    }

    public IProtocol build() throws Exception {
        try {
            final Class<?>[] ctrClasses = { Map.class };
            final Object[] args = { getConstructor() };
            return (IProtocol) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (final Exception e) {
            System.err.println("Exception thrown while building the protocol plugin from spec: " + e.getMessage());
            System.exit(1);
            return null;
        }
    }

    protected Set<String> getRequiredConstructorKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("endpoints");
        return set;
    }

}
