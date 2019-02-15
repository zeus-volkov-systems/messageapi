package gov.noaa.messageapi.fieldsets;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IFieldSet;
import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.fields.SimpleField;


public class FieldSet implements IFieldSet {

    protected String name = null;
    protected String namespace = null;
    protected List<IField> fields = null;

    @SuppressWarnings("unchecked")
    public FieldSet(Map<String,Object> fieldMap) {
        setName((String) fieldMap.get("name"));
        setNamespace((String) fieldMap.get("namespace"));
        initialzeFields((List<String>) fieldMap.get("fields"));
    }

    public FieldSet(IFieldSet fieldSet) {
        setName(fieldSet.getName());
        setNamespace(fieldSet.getNamespace());
        setFields(fieldSet.getFields());
    }

    public FieldSet getCopy() {
        return new FieldSet(this);
    }

    public String getName() {
        return this.name;
    }

    public String getNamespace() {
        return this.namespace;
    }

    public List<IField> getFields() {
        return this.fields;
    }


    private void setName(String name) {
        this.name = name;
    }

    private void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    private void initialzeFields(List<String> fieldNames) {
        this.fields = fieldNames.stream()
            .map(name -> new SimpleField(name)).collect(Collectors.toList());
    }

    public void setFields(List<IField> fields) {
        this.fields = fields.stream().map(f -> {
            try {
                IField newField = new SimpleField(f);
                return newField;
            } catch (Exception e) {
                return null;
            }
        }).collect(Collectors.toList());
    }

}
