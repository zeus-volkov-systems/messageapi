package gov.noaa.messageapi.parsers.plugins;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.parsers.plugins.BasePluginParser;
import gov.noaa.messageapi.interfaces.IPluginParser;

public class ProtocolPluginParser extends BasePluginParser implements IPluginParser {

    public ProtocolPluginParser(Object protocolMap) throws Exception {
        super(protocolMap);
    }

    public IProtocol build() throws Exception {
        try {
            Class<?>[] ctrClasses = {Map.class};
            Object[] args = {getConstructor()};
            return (IProtocol) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (Exception e) {
            return null;
        }
    }

    protected Set<String> getRequiredConstructorKeys() {
        Set<String> set = new HashSet<String>();
        set.add("metadata");
        return set;
    }

}
