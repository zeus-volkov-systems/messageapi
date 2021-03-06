package gov.noaa.messageapi.connections;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;
import java.lang.reflect.Constructor;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IEndpoint;

import gov.noaa.messageapi.definitions.ContainerDefinition;

import gov.noaa.messageapi.utils.general.ListUtils;

/**
 * @author Ryan Berkheimer
 */
public class BaseConnection {

    private IEndpoint endpoint = null;
    private String endpointClass = null;
    private Map<String,Object> constructorMap = null;

    @SuppressWarnings("unchecked")
    public BaseConnection(final String endpointClass, final Map<String, Object> connectionMap,
            final ContainerDefinition containerDefinition) throws Exception {
        try {
            final Map<String, Object> constructorMap = (Map<String, Object>) connectionMap.get("constructor");
            this.updateConstructorMap(connectionMap, constructorMap, containerDefinition);
            this.setEndpointClass(endpointClass);
            this.setEndpointConstructor(constructorMap);
            this.setEndpoint(endpointClass, constructorMap);
        } catch (final Exception e) {
            throw new InstantiationException(String.format(
                    "Could not initialize the base connection class from the specified class %s.", endpointClass));
        }
    }

    public BaseConnection(final IConnection connection) throws Exception {
        try {
            this.setEndpointClass(connection.getEndpointClass());
            this.setEndpointConstructor(connection.getEndpointConstructor());
            this.setEndpoint(this.getEndpointClass(), this.getEndpointConstructor());
        } catch (final Exception e) {
            throw new InstantiationException(
                    "Could not initialize the base connection class from the passed existing connection object.");
        }
    }

    public String getEndpointClass() {
        return this.endpointClass;
    }

    public Map<String, Object> getEndpointConstructor() {
        return this.constructorMap;
    }

    protected IEndpoint getEndpoint() {
        return this.endpoint;
    }

    private void updateConstructorMap(final Map<String, Object> connectionMap, final Map<String, Object> constructorMap,
            final ContainerDefinition containerDefinition) throws Exception {
        final Map<String, Object> parameterMap = new HashMap<String, Object>();
        if (connectionMap.containsKey("fields")) {
            parameterMap.put("fields", this.parseFields(connectionMap.get("fields")));
        } else {
            parameterMap.put("fields", new ArrayList<String>());
        }
        if (connectionMap.containsKey("collections")) {
            parameterMap.put("collections",
                    this.parseCollections(connectionMap.get("collections"), containerDefinition.getCollections()));
        } else {
            parameterMap.put("collections", new ArrayList<String>());
        }
        if (connectionMap.containsKey("classifiers")) {
            parameterMap.put("classifiers",
                    this.parseClassifiers(connectionMap.get("classifiers"), containerDefinition.getClassifiers()));
        } else {
            parameterMap.put("classifiers", new ArrayList<Map.Entry<String, String>>());
        }
        if (connectionMap.containsKey("transformations")) {
            parameterMap.put("transformations", this.parseTransformations(connectionMap.get("transformations"),
                    containerDefinition.getTransformations()));
        } else {
            parameterMap.put("transformations", new ArrayList<Map<String, Object>>());
        }
        constructorMap.put("__internal__", parameterMap);
    }

    @SuppressWarnings("unchecked")
    private List<String> parseFields(final Object fields) {
        if (fields instanceof List) {
            return (List<String>) fields;
        } else {
            return new ArrayList<String>();
        }
    }

    @SuppressWarnings("unchecked")
    private List<String> parseCollections(final Object rawCollections, final List<String> allCollections)
            throws Exception {
        try {
            if (rawCollections instanceof String) {
                if (((String) rawCollections).equals("*")) {
                    return new ArrayList<String>(allCollections);
                } else {
                    final List<String> collections = new ArrayList<String>();
                    if (allCollections.contains((String) rawCollections)) {
                        collections.add((String) rawCollections);
                    }
                    return collections;
                }
            } else if (rawCollections instanceof List) {
                if (((List<String>) rawCollections).contains("*")) {
                    return new ArrayList<String>(allCollections);
                } else {
                    return ((List<String>) rawCollections).stream().filter(rC -> allCollections.contains(rC))
                            .collect(Collectors.toList());
                }
            }
            return new ArrayList<String>();
        } catch (final Exception e) {
            throw new Exception("Error while attempting to parse internal collections in BaseCollection.");
        }
    }

    @SuppressWarnings("unchecked")
    private List<Map.Entry<String, String>> parseClassifiers(final Object rawClassifiers,
            final List<Map.Entry<String, String>> allClassifiers) throws Exception {
        try {
            if (rawClassifiers instanceof String && rawClassifiers.equals("*")) {
                return allClassifiers;
            } else if (rawClassifiers instanceof Map) {
                return ListUtils.flatten(((Map<String, Object>) rawClassifiers).entrySet().stream().map(e -> {
                    if (e.getValue() instanceof List) {
                        if (((List<String>) e.getValue()).size() == 1
                                && ((List<String>) e.getValue()).get(0).equals("*")) {
                            return allClassifiers.stream().filter(c -> c.getKey().equals(e.getKey()))
                                    .collect(Collectors.toList());
                        } else {
                            return ListUtils.flatten(((List<String>) e.getValue()).stream().map(c -> {
                                return allClassifiers.stream()
                                        .filter(allc -> (allc.getKey().equals(e.getKey()) && allc.getValue().equals(c)))
                                        .collect(Collectors.toList());
                            }).collect(Collectors.toList()));
                        }
                    } else if (e.getValue() instanceof String) {
                        if (((String) e.getValue()).equals("*")) {
                            return allClassifiers.stream().filter(c -> c.getKey().equals(e.getKey()))
                                    .collect(Collectors.toList());
                        } else {
                            return allClassifiers.stream()
                                    .filter(c -> (c.getKey().equals(e.getKey()) && c.getValue().equals(e.getValue())))
                                    .collect(Collectors.toList());
                        }
                    }
                    return null;
                }).collect(Collectors.toList()));
            }
            return new ArrayList<Map.Entry<String, String>>();
        } catch (final Exception e) {
            throw new Exception("Error while attempting to parse collections in BaseCollection.");
        }
    }

    @SuppressWarnings("unchecked")
    private List<String> parseTransformations(final Object rawTransformations, final List<String> allTransformations)
            throws Exception {
        try {
            if (rawTransformations instanceof String) {
                if (((String) rawTransformations).equals("*")) {
                    return allTransformations;
                } else {
                    final List<String> transformations = new ArrayList<String>();
                    if (allTransformations.contains((String) rawTransformations)) {
                        transformations.add((String) rawTransformations);
                    }
                    return transformations;
                }
            } else if (rawTransformations instanceof List) {
                if (((List<String>) rawTransformations).contains("*")) {
                    return new ArrayList<String>(allTransformations);
                } else {
                    return ((List<String>) rawTransformations).stream().filter(rT -> allTransformations.contains(rT))
                            .collect(Collectors.toList());
                }
            }
            return new ArrayList<String>();
        } catch (final Exception e) {
            throw new Exception("Error while attempting to parse internal collections in BaseCollection.");
        }

    }

    private IEndpoint initializeConnection(final String endpoint, final Map<String, Object> constructor)
            throws Exception {
        final Class<?>[] ctrClasses = { Map.class };
        final Object[] args = { constructor };
        return (IEndpoint) instantiateEndpoint(Class.forName(endpoint), ctrClasses, args);
    }

    private Object instantiateEndpoint(final Class<?> pluginClass, final Class<?>[] ctrClasses, final Object[] args)
            throws Exception {
        final Constructor<?> constructor = pluginClass.getDeclaredConstructor(ctrClasses);
        return constructor.newInstance(args);
    }

    private void setEndpointConstructor(final Map<String, Object> constructorMap) {
        this.constructorMap = constructorMap;
    }

    private void setEndpointClass(final String endpointClass) {
        this.endpointClass = endpointClass;
    }

    protected void setEndpoint(final String endpointClass, final Map<String, Object> constructorMap) throws Exception {
        this.endpoint = this.initializeConnection(endpointClass, constructorMap);
    }

}
