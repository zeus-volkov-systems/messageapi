package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IPluginParser;
import gov.noaa.messageapi.parsers.plugins.BasePluginParser;

/**
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
        //set.add("metadata");
        set.add("fields");
        return set;
    }

}
