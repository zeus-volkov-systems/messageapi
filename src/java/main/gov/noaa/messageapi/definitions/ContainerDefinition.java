package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import gov.noaa.messageapi.parsers.containers.MetadataParser;
import gov.noaa.messageapi.parsers.containers.CollectionParser;
import gov.noaa.messageapi.parsers.containers.TransformationParser;

/**
 * A container definition holds the definition of a container. It essentially
 * acts as a blueprint for use by instantiated containers, separating out
 * what a container is from how it is used. Container Definitions hold things
 * like container record definitions. This class is used by the session factory
 * to bootstrap new containers from a configurable specification.
 */
public class ContainerDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> collectionMaps = null;
    private List<Map<String,Object>> transformationMaps = null;

    public ContainerDefinition(Map<String, Object> properties) throws Exception {
        parseMetadataSpec((String) properties.get("metadata"));
        parseCollectionSpec((String) properties.get("collections"));
        parseTransformationSpec((String) properties.get("transformations"));
    }

    public ContainerDefinition(ContainerDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.collectionMaps = new ArrayList<Map<String,Object>>(definition.getCollectionMaps());
        this.transformationMaps = new ArrayList<Map<String,Object>>(definition.getTransformationMaps());
    }

    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    private void parseCollectionSpec(String spec) throws Exception {
        CollectionParser parser = new CollectionParser(spec);
        this.collectionMaps = parser.getCollectionMaps();
    }

    private void parseTransformationSpec(String spec) throws Exception {
        TransformationParser parser = new TransformationParser(spec);
        this.transformationMaps = parser.getTransformationMaps();
    }

    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    public List<Map<String,Object>> getCollectionMaps() {
        return this.collectionMaps;
    }

    public List<Map<String,Object>> getTransformationMaps() {
        return this.transformationMaps;
    }

}
