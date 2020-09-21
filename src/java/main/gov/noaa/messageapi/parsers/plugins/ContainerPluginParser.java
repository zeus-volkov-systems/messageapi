package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IPluginParser;

/**
 * This class builds the container plugin from the session spec.
 * @author Ryan Berkheimer
 */
public class ContainerPluginParser extends BasePluginParser implements IPluginParser {

    public ContainerPluginParser(final Object containerMap) throws Exception {
        super(containerMap);
    }

    public IContainer build() throws Exception {
        try {
            final Class<?>[] ctrClasses = { Map.class };
            final Object[] args = { getConstructor() };
            return (IContainer) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (final Exception e) {
            System.err.println("Exception thrown while building the container plugin from spec: " + e.getMessage());
            System.exit(1);
            return null;
        }
    }

    protected Set<String> getRequiredConstructorKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("collections");
        return set;
    }

}
