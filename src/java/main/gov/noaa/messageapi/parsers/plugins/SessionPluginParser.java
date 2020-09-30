package gov.noaa.messageapi.parsers.plugins;

import java.util.Set;
import java.util.Map;
import java.util.HashSet;

import gov.noaa.messageapi.interfaces.ISession;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.ISchema;

import gov.noaa.messageapi.interfaces.IPluginParser;

/**
 * This class builds the session plugin from the manifest. A session is made up of
 * container, protocol, and schema so this class builds those in turn.
 * @author Ryan Berkheimer
 */
public class SessionPluginParser extends BasePluginParser implements IPluginParser {

    public SessionPluginParser(final String spec) throws Exception {
        super(spec);
    }

    public SessionPluginParser(final Object parserMap) throws Exception {
        super(parserMap);
    }

    @SuppressWarnings("unchecked")
    public ISession build() throws Exception {
        try {
            final Map<String, Object> constructor = getConstructor();
            final IContainer container = buildContainer((Map<String, Object>) constructor.get("container"));
            final IProtocol protocol = buildProtocol((Map<String, Object>) constructor.get("protocol"));
            final ISchema schema = buildSchema((Map<String, Object>) constructor.get("schema"));
            final Class<?>[] ctrClasses = { IContainer.class, IProtocol.class, ISchema.class };
            final Object[] args = { container, protocol, schema };
            return (ISession) constructPlugin(Class.forName(getPlugin()), ctrClasses, args);
        } catch (final Exception e) {
            System.err.println("Exception thrown while building the session plugin from spec: " + e.getMessage());
            System.exit(1);
            return null;
        }
    }

    private IContainer buildContainer(final Map<String, Object> containerMap) throws Exception {
        return (IContainer) new ContainerPluginParser(containerMap).build();
    }

    private IProtocol buildProtocol(final Map<String, Object> protocolMap) throws Exception {
        return (IProtocol) new ProtocolPluginParser(protocolMap).build();
    }

    private ISchema buildSchema(final Map<String, Object> schemaMap) throws Exception {
        return (ISchema) new SchemaPluginParser(schemaMap).build();
    }

    protected Set<String> getRequiredConstructorKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("container");
        set.add("protocol");
        set.add("schema");
        return set;
    }


}
