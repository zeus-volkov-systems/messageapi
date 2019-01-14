package gov.noaa.messageapi.schemas.simple;

import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IOperator;

import gov.noaa.messageapi.schemas.BaseSchema;
import gov.noaa.messageapi.records.schema.SchemaRecord;

public class SimpleSchema extends BaseSchema implements ISchema {

    private static final Logger logger = LogManager.getLogger();

    public SimpleSchema(Map<String, Object> properties) {
        super(properties);
    }

    public SimpleSchema(ISchema schema) {
        super(schema);
    }

    public ISchema getCopy() {
        return new SimpleSchema(this);
    }

    public void initialize(IContainer c, IProtocol p) {
        try {
            this.createSchemaDefinition(this.getProperties());
        } catch (Exception e) {
            logger.error("Could not create schema definition.");
        }
    }

    public IRecord createRecord() {
        return new SchemaRecord(this.definition.getFieldMaps(), this.definition.getConditionMaps());
    }

    public IOperator getOperator(String type) {
        return this.definition.getOperatorFactory().getOperator(type);
    }

    public String getType() {
        return (String) this.definition.getMetadataMap().get("type");
    }

    public String getName() {
        return (String) this.definition.getMetadataMap().get("name");
    }

}
