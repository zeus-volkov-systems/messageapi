package gov.noaa.messageapi.records.container;

import gov.noaa.messageapi.interfaces.IField;
import java.util.List;

import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.interfaces.IRelationship;

public class BaseUnit {

    protected String name = null;
    protected String namespace = null;
    private String type = null;
    protected IRelationship relationship = null;
    protected List<IField> fields = null;
    protected List<IContainerUnit> children = null;

    public BaseUnit(String type) {
        setType(type);
    }

    public BaseUnit(){}

    public String getName() {
        return this.name;
    }

    public String getNamespace() {
        return this.namespace;
    }

    public String getType() {
        return this.type;
    }

    public IRelationship getRelationship() {
        return this.relationship;
    }

    public List<IField> getFields() {
        return this.fields;
    }

    public List<IContainerUnit> getChildren() {
        return this.children;
    }

    public void setType(String type) {
        this.type = type;
    }

}
