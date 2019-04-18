package gov.noaa.messageapi.transformations;

import java.util.Map;
import java.util.List;
import java.util.HashMap;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.fields.DefaultField;

public class JoinTransformation implements ITransformation {

    private IField joinField = null;
    private IField collectionField = null;

    public JoinTransformation(List<String> fields, Map<String,Object> params) {
        setJoinField((String) params.get("join_field"));
        setCollectionField((String) params.get("collection_field"));
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        return transformationMap.get("test");
    }

    public IField getJoinField() {
        return this.joinField;
    }

    public IField getCollectionField() {
        return this.collectionField;
    }

    private void setCollectionField(String collectionField) {
        this.collectionField = new DefaultField(makeCollectionFieldMap(collectionField));
    }

    private void setJoinField(String joinField) {
        this.joinField = new DefaultField(makeJoinFieldMap(joinField));
    }

    private Map<String,Object> makeJoinFieldMap(String joinField) {
        Map<String,Object> fieldMap = new HashMap<String,Object>();
        fieldMap.put("id", joinField);
        fieldMap.put("required", true);
        return fieldMap;
    }

    private Map<String,Object> makeCollectionFieldMap(String collectionField) {
        Map<String,Object> fieldMap = new HashMap<String,Object>();
        fieldMap.put("id", collectionField);
        fieldMap.put("type", "List<IRecord>");
        fieldMap.put("required", true);
        return fieldMap;
    }

}
