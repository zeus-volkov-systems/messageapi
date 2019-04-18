package gov.noaa.messageapi.records.schema;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICondition;
import gov.noaa.messageapi.fields.DefaultField;
import gov.noaa.messageapi.factories.ConditionTypeFactory;

public class SchemaRecord implements IRecord {


    private List<IField> fields = null;
    private List<ICondition> conditions = null;
    private boolean valid = true;

    public SchemaRecord(List<Map<String,Object>> fieldMaps, List<Map<String,Object>> conditionMaps) {
        initializeFields(fieldMaps);
        initializeConditions(conditionMaps);
    }

    public SchemaRecord(IRecord record) {
        setFields(record.getFields());
        setConditions(record.getConditions());
    }

    public SchemaRecord(List<IField> fields) {
        setFields(fields);
    }

    public SchemaRecord(IRecord record, List<Map<String,Object>> fieldMaps) {
        initializeFields(fieldMaps);
        setConditions(record.getConditions());
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

    public IField getField(String fieldName) {
        try {
            return this.fields.stream().filter(field -> field.getName().equals(fieldName))
                                .findFirst().get();
        } catch (Exception e) {
            return null;
        }
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

    public List<ICondition> getConditions() {
        return this.conditions;
    }

    public void setValid(boolean valid) {
        this.valid = valid;
    }

    public boolean isValid() {
        return this.valid;
    }

}
