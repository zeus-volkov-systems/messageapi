package gov.noaa.messageapi.definitions;

import java.util.Map;
import java.util.List;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IConditionFactory;
import gov.noaa.messageapi.interfaces.IConditionOperator;
import gov.noaa.messageapi.parsers.schemas.MetadataParser;
import gov.noaa.messageapi.parsers.schemas.FieldParser;
import gov.noaa.messageapi.parsers.schemas.ConditionParser;
import gov.noaa.messageapi.parsers.schemas.ConditionOperatorParser;

import gov.noaa.messageapi.enums.ConditionStrategy;
import gov.noaa.messageapi.exceptions.ConfigurationParsingException;
import gov.noaa.messageapi.exceptions.MessageApiException;

/**
 * A SchemaDefinition is used to parse a specified
 * configuration and create a blueprint for how the user interacts with
 * a session. SchemaDefinitions hold raw and/or simple datatypes to be turned
 * held, referenced, and converted to more complex types over the course of
 * requests, by parent Schemas and Requests. SchemaDefinitions should try
 * to hold as little, simple data as possible in order to maintain performance
 * in construction.
 * @author Ryan Berkheimer
 */
public class SchemaDefinition {

    private Map<String,Object> metadataMap = null;
    private List<Map<String,Object>> fieldMaps = null;
    private List<Map<String,Object>> conditionMaps = null;
    private IConditionFactory conditionOperatorFactory = null;
    private Enum<ConditionStrategy> conditionStrategy = null;
    private Map<String,Map<String,Object>> conditionOperatorMap = null;

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
    public SchemaDefinition(final Map<String, Object> properties) throws Exception {
        if (properties.containsKey("metadata")) {
            this.parseMetadataSpec((String) properties.get("metadata"));
        } else {
            this.setEmptyMetadata();
        }
        if (properties.containsKey("fields")) {
            this.parseFieldSpec((String) properties.get("fields"));
        } else {
            throw new ConfigurationParsingException("Missing necessary 'fields' key when parsing schema definition.");
        }
        if (properties.containsKey("conditions")) {
            this.parseConditions(properties.get("conditions"));
        } else {
            this.setEmptyConditions();
        }
    }

    /**
     * Copy constructor for SchemaDefinition. In the context of the Storage Service,
     * this constructor is used to maintain copies of the schema definition
     * per-request. This ensures no issues will be caused in the case that the
     * definition is ever modified by another action during a specific request. The
     * definition of a schema SHOULD be immutable, however the configurability of
     * the service makes this impossible to guarantee.
     * 
     * @param definition The original schema definition for the service when the
     *                   request was submitted.
     */
    public SchemaDefinition(final SchemaDefinition definition) {
        this.metadataMap = new HashMap<String, Object>(definition.getMetadataMap());
        this.fieldMaps = new ArrayList<Map<String, Object>>(definition.getFieldMaps());
        this.conditionMaps = new ArrayList<Map<String, Object>>(definition.getConditionMaps());
        this.conditionStrategy = definition.getConditionStrategy();
        if (definition.getConditionStrategy().equals(ConditionStrategy.FACTORY)) {
            this.conditionOperatorFactory = definition.getOperatorFactory().getCopy();
        } else if (definition.getConditionStrategy().equals(ConditionStrategy.SPEC)) {
            this.conditionOperatorMap = definition.getConditionOperatorMap();
        }
    }

    /**
     * This method constructs the operator factory used by certain request
     * comparisons. This class is bootstrapped at runtime to provide the user with
     * an ability to either extend a basic set of comparisons, or specify complex or
     * customized comparison types (on object values).
     * 
     * @param operatorClass A class that defines operators used in condition-field
     *                      comparisons
     * @throws Exception Throws an exception if there is an error loading the
     *                   operator class.
     */
    private void createOperatorFactory(final String operatorClass) throws Exception {
        this.conditionOperatorFactory = ConditionOperatorParser.buildFactory(operatorClass);
    }

    @SuppressWarnings("unchecked")
    private void createConditionOperatorMap(final List<Map<String,Object>> conditionMaps) throws Exception {
        try {
            List<Map<String,Object>> conditionOperatorList = conditionMaps.stream().map(cmap -> {
                Map<String,Object> externalMap = new HashMap<String,Object>();
                Map<String,Object> internalMap = new HashMap<String,Object>();
                try {
                    internalMap.put("class", ConditionOperatorParser.buildOperatorClass((String)cmap.get("operator")));
                } catch (Exception e) {
                    return null;
                }
                if (cmap.containsKey("constructor")) {
                    internalMap.put("constructor", (Map<String,Object>)cmap.get("constructor"));
                }
                externalMap.put("id", (String)cmap.get("id"));
                externalMap.put("map", internalMap);
                return externalMap;
            }).collect(Collectors.toList());
            this.conditionOperatorMap = conditionOperatorList.stream()
                    .collect(Collectors.toMap(m -> (String) m.get("id"), m -> (Map<String, Object>) m.get("map")));
        } catch (Exception e) {
            throw new MessageApiException("Condition Operator Map creation failed. Check your configuration.");
        }
    }

    /**
     * Parses a metadata map from a location specified by a string. This map holds
     * metadata information related to a user schema - a type, a schema name, etc.
     * 
     * @param spec A string pointing to a JSON map containing a schema metadata
     *             spec.
     * @throws Exception Throws an exception in the case that the map could not be
     *                   parsed.
     */
    private void parseMetadataSpec(final String spec) throws Exception {
        final MetadataParser parser = new MetadataParser(spec);
        this.metadataMap = parser.getMetadataMap();
    }

    /**
     * Parses a field map from a location specified by a string. This map holds a
     * flat list of fields that the user will interact with through the record
     * interface. Every field holds a set of properties.
     * 
     * @param spec A string pointing to a JSON map containing a schema field spec.
     * @throws Exception Throws an exception in the case that the map could not be
     *                   parsed.
     */
    private void parseFieldSpec(final String spec) throws Exception {
        final FieldParser parser = new FieldParser(spec);
        this.fieldMaps = parser.getFieldMaps();
    }

    @SuppressWarnings("unchecked")
    private void parseConditions(Object conditionValue) throws Exception {
        if (conditionValue instanceof String) {
            this.parseConditionsFromSpec((String) conditionValue);
        } else if (conditionValue instanceof Map) {
            this.parseConditionsFromManifest((Map<String, String>) conditionValue);
        }
    }

    private void parseConditionsFromSpec(String conditionSpec) throws Exception {
        try {
            final ConditionParser parser = new ConditionParser(conditionSpec);
            this.conditionMaps = parser.getConditionMaps();
            this.setConditionStrategy(ConditionStrategy.SPEC);
            this.createConditionOperatorMap(this.conditionMaps);
        } catch (Exception e) {
            throw new ConfigurationParsingException("Attempted to parse conditions (spec type) but failed.");
        }
    }

    /**
     * Parses a condition map from a location specified by a string and a factory
     * from a given class string. The condition map holds a flat list of conditions
     * that the user will interact with through the record interface. Every
     * condition holds a set of properties. Properties of conditions are mostly
     * immutable, except for values of basic comparison conditions. The factory
     * class usually should contain switches for each condition operator referenced
     * in a condition map. If no factory is provided, the default factory is used,
     * which handles basic (=, /=, <, >, <=, >=) operations on basic (boolean,
     * float, double, int, string, datetime) datatypes. If no conditions are found,
     * currently the
     * 
     * @param conditionMap A conditionMap containing map and factory keywords
     * @throws Exception Throws an exception in the case that the map could not be
     *                   parsed.
     */
    private void parseConditionsFromManifest(final Map<String, String> conditionMap) throws Exception {
        if (conditionMap.containsKey("map")) {
            try {
                final ConditionParser parser = new ConditionParser((String) conditionMap.get("map"));
                this.conditionMaps = parser.getConditionMaps();
                if (conditionMap.containsKey("factory")) {
                    this.createOperatorFactory((String) conditionMap.get("factory"));
                } else {
                    this.createOperatorFactory(DEFAULT_OPERATOR_FACTORY);
                }
                this.setConditionStrategy(ConditionStrategy.FACTORY);
            } catch (Exception e) {
                throw new ConfigurationParsingException("Attempted to parse conditions (factory type) but failed.");
            }
        } else {
            this.setEmptyConditions();
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

    /**
     * Returns a new operator instance corresponding to the class referenced by the given methodId.
     * This method is used in the case that the ConditionStrategy is SPEC (i.e., classes are directly
     * specified in the parameter map.)
     * @param methodId
     * @return
     */
    public IConditionOperator getOperator(String methodId) throws Exception {
        return ConditionOperatorParser.constructOperatorInstance(this.conditionOperatorMap.get(methodId));
    }

    /**
     * sets empty conditions on the definition, in the case that we aren't using conditions.
     */
    private void setEmptyConditions() throws Exception {
        this.conditionMaps = new ArrayList<Map<String,Object>>();
        this.createOperatorFactory(DEFAULT_OPERATOR_FACTORY);
        this.setConditionStrategy(ConditionStrategy.FACTORY);
    }

    /**
     * sets empty metadata on the definition, in the case that we aren't using metadata.
     */
    private void setEmptyMetadata() throws Exception {
        this.metadataMap = new HashMap<String,Object>();
    }

    private void setConditionStrategy(Enum<ConditionStrategy> conditionStrategy) {
        this.conditionStrategy = conditionStrategy;
    }

    public Enum<ConditionStrategy> getConditionStrategy() {
        return this.conditionStrategy;
    }

    public Map<String,Map<String,Object>> getConditionOperatorMap() {
        return this.conditionOperatorMap;
    }

}
