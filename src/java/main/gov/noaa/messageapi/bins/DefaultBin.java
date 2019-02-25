package gov.noaa.messageapi.bins;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IBin;
import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.fields.DefaultField;


public class DefaultBin implements IBin {

    protected String id = null;
    protected Map<String,Object> classifiers = null;
    protected List<IField> fields = null;

    @SuppressWarnings("unchecked")
    public DefaultBin(Map<String,Object> fieldMap) {
        setId((String) fieldMap.get("name"));
        setClassifiers((Map<String,Object>) fieldMap.get("classifiers"));
        initializeFields((List<String>) fieldMap.get("fields"));
    }

    public DefaultBin(IBin bin) {
        setId(bin.getId());
        setClassifiers(bin.getClassifiers());
        setFields(bin.getFields());
    }

    public DefaultBin getCopy() {
        return new DefaultBin(this);
    }

    public String getId() {
        return this.id;
    }

    public Map<String,Object> getClassifiers() {
        return this.classifiers;
    }

    public List<IField> getFields() {
        return this.fields;
    }

    public Object getClassifier(String classiferKey) {
        return this.classifiers.get(classiferKey);
    }

    private void setId(String id) {
        this.id = id;
    }

    private void setClassifiers(Map<String,Object> classifiers) {
        this.classifiers = classifiers;
    }

    private void initializeFields(List<String> fieldNames) {
        this.fields = fieldNames.stream()
            .map(name -> new DefaultField(name)).collect(Collectors.toList());
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

}
