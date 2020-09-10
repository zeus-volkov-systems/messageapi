package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.stream.Collectors;


import gov.noaa.messageapi.parsers.containers.MetadataParser;
import gov.noaa.messageapi.parsers.containers.CollectionParser;
import gov.noaa.messageapi.parsers.containers.TransformationParser;

/**
 * A container definition holds the definition of a container. It essentially
 * acts as a blueprint for use by instantiated containers, separating out
 * what a container is from how it is used. Container Definitions hold things
 * like container record definitions. This class is used by the session factory
 * to bootstrap new containers from a configurable specification.
 * @author Ryan Berkheimer
 */
public class ContainerDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> collectionMaps = null;
    private List<Map<String,Object>> transformationMaps = null;
    private List<String> collections = null;
    private List<String> transformations = null;
    private List<Map.Entry<String,String>> classifiers = null;

    public ContainerDefinition(Map<String, Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            this.parseMetadataSpec((String) properties.get("metadata"));
        } else {
            this.setEmptyMetadata();
        }
        if (properties.containsKey("collections")) {
            this.parseCollectionSpec((String) properties.get("collections"));
        } else {
            throw new Exception("Missing necessary 'collections' key when parsing container definition.");
        }
        if (properties.containsKey("transformations")) {
            this.parseTransformationSpec(properties.get("transformations"));
        } else {
            this.setEmptyTransformationMaps();
        }
    }

    public ContainerDefinition(ContainerDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.collectionMaps = new ArrayList<Map<String,Object>>(definition.getCollectionMaps());
        this.collections = new ArrayList<String>(definition.getCollections());
        this.classifiers = new ArrayList<Map.Entry<String,String>>(definition.getClassifiers());
        this.transformations = new ArrayList<String>(definition.getTransformations());
        this.transformationMaps = new ArrayList<Map<String,Object>>(definition.getTransformationMaps());
    }

    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    private void parseCollectionSpec(String spec) throws Exception {
        CollectionParser parser = new CollectionParser(spec);
        this.collectionMaps = parser.getCollectionMaps();
        this.collections = parser.getCollections();
        this.classifiers = parser.getClassifiers();
    }

    @SuppressWarnings("unchecked")
    private void parseTransformationSpec(Object transformationSpec) throws Exception {
        try {
            if (transformationSpec instanceof String) {
                TransformationParser parser = new TransformationParser(((String) transformationSpec));
                this.transformationMaps = parser.getTransformationMaps();
                this.transformations = parser.getTransformations();
            } else if (transformationSpec instanceof List) {
                TransformationParser parser = new TransformationParser((List<Map<String,Object>>)transformationSpec);
                this.transformationMaps = parser.getTransformationMaps();
                this.transformations = parser.getTransformations();
            } else {
                this.setEmptyTransformationMaps();
            }
        } catch (Exception e) {
            System.out.println("WARNING - transformation parsing failed. Setting empty transformations.");
            this.setEmptyTransformationMaps();
        }
    }

    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    public List<Map<String,Object>> getCollectionMaps() {
        return this.collectionMaps;
    }

    public List<String> getCollections() {
        return this.collections;
    }

    public List<Map.Entry<String,String>> getClassifiers() {
        return this.classifiers;
    }

    public List<String> getClassifierKeys() {
        return this.classifiers.stream().map(entry -> entry.getKey()).collect(Collectors.toList());
    }

    public List<String> getTransformations() {
        return this.transformations;
    }

    public List<Map<String,Object>> getTransformationMaps() {
        return this.transformationMaps;
    }

    /**
     * Sets the definition transformation maps to be empty, the transformation
     * factory to be the default.
     */
    private void setEmptyTransformationMaps() throws Exception {
        this.transformationMaps = new ArrayList<Map<String,Object>>();
        this.transformations = new ArrayList<String>();
    }

    /**
     * sets empty metadata on the definition, in the case that we aren't using
     * metadata.
     */
    private void setEmptyMetadata() throws Exception {
        this.metadataMap = new HashMap<String, Object>();
    }

}
