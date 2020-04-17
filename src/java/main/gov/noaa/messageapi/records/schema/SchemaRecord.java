package gov.noaa.messageapi.records.schema;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.fields.DefaultField;
import gov.noaa.messageapi.factories.ConditionTypeFactory;

/**
 * A SchemaRecord is the principle record type used by an end user who is
 * consuming the MessageAPI library. SchemaRecords consist of fields and
 * conditions. Conditions are optional. The user always deals in schema records -
 * schema records are submitted in requests, and responses return schema records.
 * @author Ryan Berkheimer
 */
public class SchemaRecord implements IRecord {


    private List<IField> fields = null;
    private List<ICondition> conditions = null;
    private Boolean valid = true;

    public SchemaRecord(List<Map<String,Object>> fieldMaps, List<Map<String,Object>> conditionMaps) {
        this.initializeFields(fieldMaps);
        this.initializeConditions(conditionMaps);
    }

    public SchemaRecord(IRecord record) {
        this.setFields(record.getFields());
        if (record.getConditions() != null) {
            this.setConditions(record.getConditions());
        }
    }

    /**
     * Creates a new SchemaRecord from a list of IFields.
     * When this constructor is used, the IFields passed are all copied
     * into new IField instances for parallelization safety
     * @param fields A list of IFields which will be used to create new IFields
     * and add to a SchemaRecord
     */
    public SchemaRecord(List<IField> fields) {
        this.setFields(fields);
    }

    public SchemaRecord(IRecord record, List<Map<String,Object>> fieldMaps) {
        this.initializeFields(fieldMaps);
        this.setConditions(record.getConditions());
    }

    public SchemaRecord getCopy() {
        return new SchemaRecord(this);
    }

    private void initializeFields(List<Map<String,Object>> fieldMaps) {
        this.fields = fieldMaps.stream().map(fieldMap -> {
                IField f = new DefaultField(fieldMap);
                return f;
            }).collect(Collectors.toList());
    }

    private void initializeConditions(List<Map<String,Object>> conditionMaps) {
        this.conditions = conditionMaps.stream().map(conditionMap -> {
            try {
                ICondition c = ConditionTypeFactory.create(conditionMap);
                return c;
            } catch (Exception e) {
                return null;
            }
        }).collect(Collectors.toList());
    }

    public void setFields(List<IField> fields) {
        this.fields = fields.stream().map(f -> {
            try {
                IField newField = new DefaultField(f);
                return newField;
            } catch (Exception e) {
                return null;
            }
        }).collect(Collectors.toList());
    }

    public void setConditions(List<ICondition> conditions) {
        this.conditions = conditions.stream().map(c -> {
            try {
                ICondition newCondition = ConditionTypeFactory.create(c);
                return newCondition;
            } catch (Exception e) {
                return null;
            }
        }).collect(Collectors.toList());
    }

    public void setField(Object field, Object fieldValue) {
        if (field instanceof String) {
            String castField = (String) field;
            try {
                this.fields.stream().filter(f -> f.getName().equals(castField))
                            .findFirst().get().setValue(fieldValue);
            } catch (Exception e) {
            }
        } else if (field instanceof IField) {
            IField castField = (IField) field;
            try {
                this.fields.stream().filter(f -> f.getName().equals(castField.getName()))
                            .findFirst().get().setValue(fieldValue);
            } catch (Exception e) {}
        }
    }

    public void setCondition(Object condition, Object conditionValue) {
        if (condition instanceof String) {
            String castCondition = (String) condition;
            try {
                this.conditions.stream().filter(c -> c.getId().equals(castCondition))
                            .findFirst().get().setValue(conditionValue);
            } catch (Exception e) {
            }
        } else if (condition instanceof ICondition) {
            ICondition castCondition = (ICondition) condition;
            try {
                this.conditions.stream().filter(c -> c.getId().equals(castCondition.getId()))
                            .findFirst().get().setValue(conditionValue);
            } catch (Exception e) {}
        }
    }

    public IField getField(String fieldId) {
        try {
            return this.fields.stream().filter(field -> field.getId().equals(fieldId))
                                .findFirst().get();
        } catch (Exception e) {
            return null;
        }
    }

    public Boolean hasField(String fieldId) {
        return this.fields.stream().filter(field -> field.getId().equals(fieldId))
                                .findFirst().isPresent();
    }

    public Boolean hasCondition(String conditionId) {
        return this.conditions.stream().filter(condition -> condition.getId().equals(conditionId))
                                    .findFirst().isPresent();
    }

    public ICondition getCondition(String conditionId) {
        try {
            return this.conditions.stream().filter(condition -> condition.getId().equals(conditionId))
                                .findFirst().get();
        } catch (Exception e) {
            return null;
        }
    }

    public List<IField> getFields() {
        return this.fields;
    }

    public List<String> getFieldIds() {
        return this.fields.stream().map(field -> field.getId()).collect(Collectors.toList());
    }

    public List<ICondition> getConditions() {
        return this.conditions;
    }

    public List<String> getConditionIds() {
        return this.conditions.stream().map(condition -> condition.getId()).collect(Collectors.toList());
    }

    public void setValid(Boolean valid) {
        this.valid = valid;
    }

    public Boolean isValid() {
        return this.valid;
    }

}
