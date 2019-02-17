package gov.noaa.messageapi.schemas;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IOperator;

import gov.noaa.messageapi.schemas.BaseSchema;
import gov.noaa.messageapi.metadata.DefaultMetadata;

import gov.noaa.messageapi.records.schema.SchemaRecord;

public class DefaultSchema extends BaseSchema implements ISchema {

    public DefaultSchema(Map<String, Object> properties) {
        super(properties);
    }

    public DefaultSchema(ISchema schema) {
        super(schema);
        this.setMetadata(schema.getDefinition().getMetadataMap());
    }

    public ISchema getCopy() {
        return new DefaultSchema(this);
    }

    public void initialize(IContainer c, IProtocol p) {
        try {
            this.createSchemaDefinition(this.getProperties());
            this.setMetadata(this.definition.getMetadataMap());
        } catch (Exception e) {}
    }

    public IRecord createRecord() {
        return new SchemaRecord(this.definition.getFieldMaps(), this.definition.getConditionMaps());
    }

    public IOperator getOperator(String type) {
        return this.definition.getOperatorFactory().getOperator(type);
    }

    public String getType() {
        return "DefaultSchema";
    }

    private void setMetadata(Map<String,Object> metadataMap) {
        this.metadata = new DefaultMetadata(metadataMap);
    }

}
