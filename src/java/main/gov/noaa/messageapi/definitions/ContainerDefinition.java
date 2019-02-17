package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import gov.noaa.messageapi.parsers.containers.MetadataParser;
import gov.noaa.messageapi.parsers.containers.BinParser;
import gov.noaa.messageapi.parsers.containers.RelationshipParser;

/**
 * A container definition holds the definition of a container. It essentially
 * acts as a blueprint for use by instantiated containers, separating out
 * what a container is from how it is used. Container Definitions hold things
 * like container record definitions. This class is used by the session factory
 * to bootstrap new containers from a configurable specification.
 */
public class ContainerDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> binMaps = null;
    private List<Map<String,Object>> relationshipMaps = null;

    public ContainerDefinition(Map<String, Object> properties) throws Exception {
        parseMetadataSpec((String) properties.get("metadata"));
        parseBinSpec((String) properties.get("bins"));
        parseRelationshipSpec((String) properties.get("relationships"));
    }

    public ContainerDefinition(ContainerDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.binMaps = new ArrayList<Map<String,Object>>(definition.getBinMaps());
        this.relationshipMaps = new ArrayList<Map<String,Object>>(definition.getRelationshipMaps());
    }

    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    private void parseBinSpec(String spec) throws Exception {
        BinParser parser = new BinParser(spec);
        this.binMaps = parser.getBinMaps();
    }

    private void parseRelationshipSpec(String spec) throws Exception {
        RelationshipParser parser = new RelationshipParser(spec);
        this.relationshipMaps = parser.getRelationshipMaps();
    }

    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    public List<Map<String,Object>> getBinMaps() {
        return this.binMaps;
    }

    public List<Map<String,Object>> getRelationshipMaps() {
        return this.relationshipMaps;
    }

}
