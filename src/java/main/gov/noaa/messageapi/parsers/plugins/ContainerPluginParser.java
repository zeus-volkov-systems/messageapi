package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.parsers.plugins.BasePluginParser;
import gov.noaa.messageapi.interfaces.IPluginParser;

public class ContainerPluginParser extends BasePluginParser implements IPluginParser {

    public ContainerPluginParser(Object containerMap) throws Exception {
        super(containerMap);
    }

    public IContainer build() throws Exception {
        try {
            Class<?>[] ctrClasses = {Map.class};
            Object[] args = {getConstructor()};
            return (IContainer) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (Exception e) {
            return null;
        }
    }

    protected Set<String> getRequiredConstructorKeys() {
        Set<String> set = new HashSet<String>();
        set.add("metadata");
        set.add("collections");
        set.add("transformations");
        return set;
    }

}
