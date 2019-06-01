package gov.noaa.messageapi.transformations.joins;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.fields.DefaultField;
import gov.noaa.messageapi.records.schema.SchemaRecord;


/**
 * This join takes two record sets, specified by 'parent' and 'child',
 * and creates record subsets of the 'child' record set that match the 'parent' record
 * on the 'join-field'. This subset is then added to the 'parent' record
 * as a new field, the 'collection-field'. The newly created modified 'parent' collection
 * is returned. Due to casting limitations in Java, this method only works for
 * fields containing 'String' values. Other type of joins, such as ints, floats, etc.
 * should use the appropriate join method for that type.
 *
 * Note: The original record sets serving as the 'parent' and 'child' in this method
 * are not modified, this method is externally side-effect free.
 *
 * Required Constructor Parameters:
 *
 * join-field: this parameter specifies which fields to look for matches
 * collection-field: this parameter specifies what to name the new field name on parent records to add the child collections
 *
 * Required Record Sets:
 *
 * parent: the record set used as the base for return. Each record on this set
 * at the time of return will potentially have another field added to it, which
 * is named after what the user sets in the constructor, containing a list of records
 * from the child subset that held a matching field on both sets.
 *
 * child: the record set used as the basis for subsets used in joining to matching
 * records on the parent record set.
 *
 * Example:
 *
 * join-field = 'icao'
 * collection-field = 'precips'
 *
 * parent = [{icao='kavl', lat='x', lon='y'}, {icao='kcle', lat='a', lon='b'}]
 * child = [{icao='kavl', day=1, precip=5}, {icao='kavl', day=1, precip=2}, {icao='kcle', day=3, precip=2}]
 *
 * return = [{icao='kavl', lat='x', lon='y', precips=[{icao='kavl', day=1, precip=5}, {icao='kavl', day=1, precip=2}]},
 *           {icao='kcle', lat='a', lon='b', precips=[{icao='kcle', day=3, precip=2}]}]
 *
 * @author Ryan Berkheimer
 */
public class StringFieldJoin implements ITransformation {

    private IField joinField = null;
    private IField collectionField = null;

    public StringFieldJoin(List<String> fields, Map<String,Object> params) {
        this.setJoinField((String) params.get("join-field"));
        this.setCollectionField((String) params.get("collection-field"));
    }

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap) {
        return transformationMap.get("parent").stream().map(parentRecord -> {
            List<IField> recordFields = parentRecord.getFields();
            IField collectionField = new DefaultField(this.getCollectionField());
            collectionField.setValue(transformationMap.get("child").stream()
            .filter(childRecord ->
            ((String)(parentRecord.getField(this.getJoinField().getId()).getValue()))
            .equals((String)(childRecord.getField(this.getJoinField().getId()).getValue()))));
            recordFields.add(collectionField);
            return new SchemaRecord(recordFields);
        }).collect(Collectors.toList());
    }

    public IField getJoinField() {
        return this.joinField;
    }

    public IField getCollectionField() {
        return this.collectionField;
    }

    private void setCollectionField(String collectionField) {
        this.collectionField = new DefaultField(this.makeCollectionFieldMap(collectionField));
    }

    private void setJoinField(String joinField) {
        this.joinField = new DefaultField(this.makeJoinFieldMap(joinField));
    }

    private Map<String,Object> makeJoinFieldMap(String joinField) {
        Map<String,Object> fieldMap = new HashMap<String,Object>();
        fieldMap.put("id", joinField);
        fieldMap.put("required", false);
        return fieldMap;
    }

    private Map<String,Object> makeCollectionFieldMap(String collectionField) {
        Map<String,Object> fieldMap = new HashMap<String,Object>();
        fieldMap.put("id", collectionField);
        fieldMap.put("type", "List<IRecord>");
        fieldMap.put("required", false);
        return fieldMap;
    }

}
