package gov.noaa.messageapi.collections;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;

import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.IField;

import gov.noaa.messageapi.fields.DefaultField;

/**
 * DefaultCollection represents a basic, standard collection, which is
 * a fundamental unit of a container. Collections are subsets of fields
 * derived from the full fieldset contained in a SchemaRecord. Collections
 * contain a list of fields, a request-global unique id, a map of classifiers
 * that help identify the collection in the context of a request/response,
 * and a list of condition ids that enable determination on whether or not
 * a given record should produce a collection.
 * @author Ryan Berkheimer
 */
public class DefaultCollection implements ICollection {

    protected String id = null;
    protected Map<String,Object> classifiers = null;
    protected List<IField> fields = null;
    protected List<String> conditionIds = null;

    @SuppressWarnings("unchecked")
    public DefaultCollection(final Map<String, Object> collectionMap) {
        this.setId((String) collectionMap.get("id"));
        if (collectionMap.containsKey("classifiers")) {
            this.setClassifiers((Map<String, Object>) collectionMap.get("classifiers"));
        } else {
            this.setClassifiers(new HashMap<String, Object>());
        }
        this.initializeFields((List<String>) collectionMap.get("fields"));
        if (collectionMap.containsKey("conditions")) {
            this.setConditionIds((List<String>) collectionMap.get("conditions"));
        } else {
            this.setConditionIds(new ArrayList<String>());
        }
    }

    public DefaultCollection(final ICollection collection) {
        this.setId(collection.getId());
        this.copyClassifiers(collection.getClassifiers());
        this.setFields(collection.getFields());
        this.setConditionIds(collection.getConditionIds());
    }

    public DefaultCollection getCopy() {
        return new DefaultCollection(this);
    }

    public String getId() {
        return this.id;
    }

    public Map<String, Object> getClassifiers() {
        return this.classifiers;
    }

    public List<IField> getFields() {
        return this.fields;
    }

    public List<String> getConditionIds() {
        return this.conditionIds;
    }

    public Object getClassifier(final String classiferKey) {
        return this.classifiers.get(classiferKey);
    }

    private void setId(final String id) {
        this.id = id;
    }

    private void copyClassifiers(final Map<String, Object> classifiers) {
        this.classifiers = classifiers;
    }

    private void setClassifiers(final Map<String, Object> classifiers) {
        this.classifiers = new HashMap<String, Object>();
        classifiers.entrySet().forEach(classifierEntry -> {
            if (classifierEntry.getValue() instanceof List) {
                this.classifiers.put(classifierEntry.getKey(), classifierEntry.getValue());
            } else {
                final List<String> classifierEntryValue = new ArrayList<String>();
                classifierEntryValue.add((String) classifierEntry.getValue().toString());
                this.classifiers.put(classifierEntry.getKey(), classifierEntryValue);
            }
        });
    }

    private void initializeFields(final List<String> fieldNames) {
        this.fields = fieldNames.stream().map(name -> new DefaultField(name)).collect(Collectors.toList());
    }

    public void setFields(final List<IField> fields) {
        this.fields = fields.stream().map(f -> {
            try {
                final IField newField = new DefaultField(f);
                return newField;
            } catch (final Exception e) {
                return null;
            }
        }).collect(Collectors.toList());
    }

    private void setConditionIds(final List<String> conditionIds) {
        this.conditionIds = conditionIds;
    }

}
