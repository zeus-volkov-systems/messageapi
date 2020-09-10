package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IPluginParser;

/**
 * This class builds the schema plugin from the session spec.
 * @author Ryan Berkheimer
 */
public class SchemaPluginParser extends BasePluginParser implements IPluginParser {

    public SchemaPluginParser(Object schemaMap) throws Exception {
        super(schemaMap);
    }

    public ISchema build() throws Exception {
        try {
            Class<?>[] ctrClasses = {Map.class};
            Object[] args = {getConstructor()};
            return (ISchema) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (Exception e) {
            return null;
        }
    }

    protected Set<String> getRequiredConstructorKeys() {
        Set<String> set = new HashSet<String>();
        set.add("fields");
        return set;
    }

}
