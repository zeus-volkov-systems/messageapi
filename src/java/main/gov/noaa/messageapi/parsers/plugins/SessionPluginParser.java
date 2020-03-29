package gov.noaa.messageapi.parsers.plugins;

import java.util.Set;
import java.util.Map;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.ISchema;

import gov.noaa.messageapi.interfaces.IPluginParser;

import gov.noaa.messageapi.parsers.plugins.BasePluginParser;
//import gov.noaa.messageapi.parsers.plugins.ContainerPluginParser;
//import gov.noaa.messageapi.parsers.plugins.ProtocolPluginParser;
//import gov.noaa.messageapi.parsers.plugins.SchemaPluginParser;

/**
 * @author Ryan Berkheimer
 */
public class SessionPluginParser extends BasePluginParser implements IPluginParser {

    public SessionPluginParser(String spec) throws Exception {
        super(spec);
    }

    @SuppressWarnings("unchecked")
    public ISession build() throws Exception {
        try {
            Map<String, Object> constructor = getConstructor();
            IContainer container = buildContainer((Map<String, Object>) constructor.get("container"));
            IProtocol protocol = buildProtocol((Map<String, Object>) constructor.get("protocol"));
            ISchema schema = buildSchema((Map<String, Object>) constructor.get("schema"));
            Class<?>[] ctrClasses = {IContainer.class, IProtocol.class, ISchema.class};
            Object[] args = {container, protocol, schema};
            return (ISession) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (Exception e) {
            return null;
        }
    }

    private IContainer buildContainer(Map<String,Object> containerMap) throws Exception {
        return (IContainer) new ContainerPluginParser(containerMap).build();
    }

    private IProtocol buildProtocol(Map<String,Object> protocolMap) throws Exception {
        return (IProtocol) new ProtocolPluginParser(protocolMap).build();
    }

    private ISchema buildSchema(Map<String,Object> schemaMap) throws Exception {
        return (ISchema) new SchemaPluginParser(schemaMap).build();
    }

    protected Set<String> getRequiredConstructorKeys() {
        Set<String> set = new HashSet<String>();
        set.add("container");
        set.add("protocol");
        set.add("schema");
        return set;
    }


}
