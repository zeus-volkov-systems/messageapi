package gov.noaa.messageapi.definitions;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IConditionFactory;
import gov.noaa.messageapi.parsers.schemas.MetadataParser;
import gov.noaa.messageapi.parsers.schemas.FieldParser;
import gov.noaa.messageapi.parsers.schemas.ConditionParser;
import gov.noaa.messageapi.parsers.schemas.ConditionOperatorParser;

/**
 * A SchemaDefinition is used by the StorageService to parse a specified
 * configuration and create a blueprint for how the user interacts with
 * a session. SchemaDefinitions hold raw and/or simple datatypes to be turned
 * held, referenced, and converted to more complex types over the course of
 * requests, by parent Schemas and Requests. SchemaDefinitions should try
 * to hold as little, simple data as possible in order to maintain performance
 * in construction.
 */
public class SchemaDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> fieldMaps = null;
    private List<Map<String,Object>> conditionMaps = null;
    private IConditionFactory conditionOperatorFactory = null;

    /**
     * This is the operator factory provided by the service. If users
     * do not wish to use their own custom operators, this included
     * factory will be used.
     */
    private static final String DEFAULT_OPERATOR_FACTORY =
        "gov.noaa.messageapi.factories.SimpleConditionFactory";


    /**
     * The primary constructor for a SchemaDefinition. The properties map
     * should contain key-value pairs which define a blueprint of what
     * a schema is composed of. These things include metadata, fields,
     * conditions, user operators, or other similar definition type data.
     * @param  properties A map containing specific schema-blueprint-related info
     * @throws Exception  An exception is thrown if there is an issue parsing the schema definition.
     */
    @SuppressWarnings("unchecked")
    public SchemaDefinition(Map<String, Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            parseMetadataSpec((String) properties.get("metadata"));
        } else {
            throw new Exception("Missing necessary 'metadata' key when parsing schema definition.");
        }
        if (properties.containsKey("fields")) {
            parseFieldSpec((String) properties.get("fields"));
        } else {
            throw new Exception("Missing necessary 'fields' key when parsing schema definition.");
        }
        if (properties.containsKey("conditions")) {
            parseConditionSpec((Map<String,String>) properties.get("conditions"));
        } else {
            throw new Exception("Missing necessary 'conditions' key when parsing schema definition.");
        }
    }

    /**
     * Copy constructor for SchemaDefinition. In the context of the Storage
     * Service, this constructor is used to maintain copies of the schema
     * definition per-request. This ensures no issues will be caused in the
     * case that the definition is ever modified by another action during
     * a specific request. The definition of a schema SHOULD be immutable,
     * however the configurability of the service makes this impossible to
     * guarantee.
     * @param definition The original schema definition for the service when
     * the request was submitted.
     */
    public SchemaDefinition(SchemaDefinition definition) {
        this.metadataMap = new HashMap<String,Object>(definition.getMetadataMap());
        this.fieldMaps = new ArrayList<Map<String,Object>>(definition.getFieldMaps());
        this.conditionMaps = new ArrayList<Map<String,Object>>(definition.getConditionMaps());
        this.conditionOperatorFactory = definition.getOperatorFactory().getCopy();
    }

    /**
     * This method constructs the operator factory used by certain request
     * comparisons. This class is bootstrapped at runtime to provide the
     * user with an ability to either extend a basic set of comparisons, or
     * specify complex or customized comparison types (on object values).
     * @param  operatorClass A class that defines operators used in condition-field comparisons
     * @throws Exception     Throws an exception if there is an error loading the operator class.
     */
    private void createOperatorFactory(String operatorClass) throws Exception {
        this.conditionOperatorFactory = ConditionOperatorParser.build(operatorClass);
    }

    /**
     * Parses a metadata map from a location specified by a string.
     * This map holds metadata information related to a user schema - a type,
     * a schema name, etc.
     * @param  spec      A string pointing to a JSON map containing a schema metadata spec.
     * @throws Exception Throws an exception in the case that the map could not be parsed.
     */
    private void parseMetadataSpec(String spec) throws Exception {
        MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    /**
     * Parses a field map from a location specified by a string.
     * This map holds a flat list of fields that the user will interact with
     * through the record interface. Every field holds a set of properties.
     * @param  spec      A string pointing to a JSON map containing a schema field spec.
     * @throws Exception Throws an exception in the case that the map could not be parsed.
     */
    private void parseFieldSpec(String spec) throws Exception {
        FieldParser parser = new FieldParser(spec);
        this.fieldMaps = parser.getFieldMaps();
    }

    /**
     * Parses a condition map from a location specified by a string and a factory from a given class string.
     * The condition map holds a flat list of conditions that the user will interact with
     * through the record interface. Every condition holds a set of properties.
     * Properties of conditions are mostly immutable, except for values of basic
     * comparison conditions.
     * The factory class usually should contain switches for each condition operator referenced
     * in a condition map. If no factory is provided, the default factory is used, which handles
     * basic (=, /=, <, >, <=, >=) operations on basic (boolean, float, double, int, string, datetime) datatypes.
     * @param  conditionMap      A conditionMap containing map and factory keywords
     * @throws Exception Throws an exception in the case that the map could not be parsed.
     */
    private void parseConditionSpec(Map<String,String> conditionMap) throws Exception {
        if (conditionMap.containsKey("factory")) {
            createOperatorFactory((String) conditionMap.get("factory"));
        } else {
            createOperatorFactory(DEFAULT_OPERATOR_FACTORY);
        }
        if (conditionMap.containsKey("conditions")) {
            ConditionParser parser = new ConditionParser((String) conditionMap.get("map"));
            this.conditionMaps = parser.getConditionMaps();
        } else {
            this.conditionMaps = new ArrayList<Map<String,Object>>();
        }
    }

    /**
     * Returns the metadata map contained by this SchemaDefintion.
     * @return A metadata map.
     */
    public Map<String,Object> getMetadataMap() {
        return this.metadataMap;
    }

    /**
     * Returns the list of field maps contained by this SchemaDefinition.
     * @return A list of field maps.
     */
    public List<Map<String,Object>> getFieldMaps() {
        return this.fieldMaps;
    }

    /**
     * Returns the list of condition maps contained by this SchemaDefinition.
     * @return A list of condition maps.
     */
    public List<Map<String,Object>> getConditionMaps() {
        return this.conditionMaps;
    }

    /**
     * Returns the Operator Factory (operator accessor) contained by this SchemaDefinition.
     * @return An OperatorFactory object.
     */
    public IConditionFactory getOperatorFactory() {
        return this.conditionOperatorFactory;
    }

}
