package gov.noaa.messageapi.endpoints;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IRecord;

import gov.noaa.messageapi.records.schema.SchemaRecord;

public abstract class BaseEndpoint {

    public List<IField> fields = null;
    public List<String> collectionIds = null;
    public List<Map.Entry<String,String>> classifierIds = null;
    public List<String> transformationIds = null;

    @SuppressWarnings("unchecked")
    public BaseEndpoint(Map<String,Object> parameters) {
        Map<String,Object> internalParameters = (Map<String,Object>)parameters.get("__internal__");
        this.setFields((List<String>)internalParameters.get("fields"), this.getDefaultFields());
        this.setCollectionIds((List<String>)internalParameters.get("collections"));
        this.setClassifierIds((List<Map.Entry<String,String>>)internalParameters.get("classifiers"));
        this.setTransformationIds((List<String>)internalParameters.get("transformations"));
    }

    public abstract List<IField> getDefaultFields();

    public IRecord createRecord() {
        return new SchemaRecord(this.getFields());
    }

    public List<String> getCollections() {
        return this.collectionIds;
    }

    public List<Map.Entry<String,String>> getClassfiers() {
        return this.classifierIds;
    }

    public List<String> getTransformations() {
        return this.transformationIds;
    }

    private List<IField> getFields() {
        return this.fields;
    }

    private void setFields(List<String> userFields, List<IField> defaultFields) {
        this.fields = this.buildFields(userFields, defaultFields);
    }

    private void setCollectionIds(List<String> collectionIds) {
        this.collectionIds = collectionIds;
    }

    private void setClassifierIds(List<Map.Entry<String,String>> classifierIds) {
        this.classifierIds = classifierIds;
    }

    private void setTransformationIds(List<String> transformationIds) {
        this.transformationIds = transformationIds;
    }

    private List<IField> buildFields(List<String> userFields, List<IField> defaultFields) {
        if (userFields.size() > 0) {
            return defaultFields.stream().filter(f -> userFields.contains(f.getId())).collect(Collectors.toList());
        }
        return defaultFields;
    }

}