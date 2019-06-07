package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ITransformationFactory;

import gov.noaa.messageapi.parsers.containers.MetadataParser;
import gov.noaa.messageapi.parsers.containers.CollectionParser;
import gov.noaa.messageapi.parsers.containers.TransformationParser;
import gov.noaa.messageapi.parsers.containers.TransformationFactoryParser;

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
    private ITransformationFactory transformationFactory = null;
    private List<String> collections = null;
    private List<String> transformations = null;
    private List<Map.Entry<String,String>> classifiers = null;


    private static final String DEFAULT_TRANSFORMATION_FACTORY =
        "gov.noaa.messageapi.factories.SimpleTransformationFactory";


    @SuppressWarnings("unchecked")
    public ContainerDefinition(Map<String, Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            this.parseMetadataSpec((String) properties.get("metadata"));
        } else {
            throw new Exception("Missing necessary 'metadata' key when parsing container definition.");
        }
        if (properties.containsKey("collections")) {
            this.parseCollectionSpec((String) properties.get("collections"));
        } else {
            throw new Exception("Missing necessary 'collections' key when parsing container definition.");
        }
        if (properties.containsKey("transformations")) {
            this.parseTransformationSpec((Map<String,String>) properties.get("transformations"));
        } else {
            throw new Exception("Missing necessary 'transformations' key when parsing container definition.");
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

    private void createTransformationFactory(String transformationClass) throws Exception {
        this.transformationFactory = TransformationFactoryParser.build(transformationClass);
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

    private void parseTransformationSpec(Map<String,String> transformationSpec) throws Exception {
        if (transformationSpec.containsKey("map")) {
            TransformationParser parser = new TransformationParser(transformationSpec.get("map"));
            this.transformationMaps = parser.getTransformationMaps();
            this.transformations = parser.getTransformations();
            if (transformationSpec.containsKey("factory")) {
                this.createTransformationFactory((String) transformationSpec.get("factory"));
            } else {
                this.createTransformationFactory(DEFAULT_TRANSFORMATION_FACTORY);
            }
        } else {
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

    public ITransformationFactory getTransformationFactory() {
        return this.transformationFactory;
    }

    /**
     * Sets the definition transformation maps to be empty, the transformation
     * factory to be the default.
     */
    private void setEmptyTransformationMaps() throws Exception {
        this.transformationMaps = new ArrayList<Map<String,Object>>();
        this.createTransformationFactory(DEFAULT_TRANSFORMATION_FACTORY);
    }

}
