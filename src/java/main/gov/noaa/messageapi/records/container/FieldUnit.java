package gov.noaa.messageapi.records.container;

import gov.noaa.messageapi.fields.SimpleField;
import java.util.stream.Collectors;
import java.util.List;
import java.util.Map;

import gov.noaa.messageapi.interfaces.IContainerUnit;
import gov.noaa.messageapi.interfaces.IRecord;

public class FieldUnit extends BaseUnit implements IContainerUnit {

    @SuppressWarnings("unchecked")
    public FieldUnit(Map<String,Object> containerMap) {
        super("container");
        setName((String) containerMap.get("name"));
        setNamespace((String) containerMap.get("namespace"));
        setFields((List<String>) containerMap.get("fields"));
    }

    public FieldUnit() {}

    public FieldUnit getCopy(IRecord r) {
        return this;
    }

    private void setName(String name) {
        this.name = name;
    }

    private void setNamespace(String namespace) {
        this.namespace = namespace;
    }

    private void setFields(List<String> fieldNames) {
        this.fields = fieldNames.stream().map(name -> new SimpleField(name)).collect(Collectors.toList());

    }

}
