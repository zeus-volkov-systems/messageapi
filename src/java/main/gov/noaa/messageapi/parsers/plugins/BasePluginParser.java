package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.lang.reflect.Constructor;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * This base parser serves as the underlayment for the other plugin parser classes.
 * It contains common logic to those plugin parsers, including validation of specific key
 * requirements and reflection object build utilities.
 * @author Ryan Berkheimer
 */
public abstract class BasePluginParser extends BaseParser {

    public BasePluginParser(final String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    public BasePluginParser(final Object parserMap) throws Exception {
        super(parserMap);
    }

    public void process() {
        if (!validateConstructorKeys(getRequiredConstructorKeys())) {
            System.err.println(String.format("Could not parse the %s plugin, invalid keyset.", getPlugin()));
            System.exit(1);
        }
    }

    protected abstract Set<String> getRequiredConstructorKeys();

    protected String getPlugin() {
        return (String) super.getValue("plugin");
    }

    @SuppressWarnings("unchecked")
    protected Map<String, Object> getConstructor() {
        return (Map<String, Object>) super.getValue("constructor");
    }

    protected Object constructPlugin(final Class<?> pluginClass, final Class<?>[] ctrClasses, final Object[] args)
            throws Exception {
        final Constructor<?> constructor = pluginClass.getDeclaredConstructor(ctrClasses);
        return constructor.newInstance(args);
    }

    protected boolean validateConstructorKeys(final Set<String> requiredKeys) {
        final Set<String> keys = getConstructor().keySet();
        if (keys.containsAll(requiredKeys)) {
            return true;
        }
        return false;
    }

    public Set<String> getRequiredKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("plugin");
        set.add("constructor");
        return set;
    }

}
