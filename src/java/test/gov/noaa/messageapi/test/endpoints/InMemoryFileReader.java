package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.packets.DefaultPacket;
import gov.noaa.messageapi.endpoints.BaseEndpoint;
import gov.noaa.messageapi.fields.DefaultField;

/**
 * <h1>InMemoryFileReader</h1> <b>Description:</b>
 * <p>
 * The core action of this endpoint is to read file(s) into memory, create a
 * record out of each line in each file, and collect all created records in a
 * list.
 * <p>
 * Files that fail to completely read for whatever reason will have all of their
 * lines rejected, and a rejection for that file will be created and added to a
 * rejections list.
 * <p>
 * The lists of assembled records and rejections will be added to the DataPacket
 * returned by this Endpoint.
 * <p>
 * This endpoint is generic enough to accept an arbitrary number of file name
 * fields and arbitrary collection(s), classifier(s), and/or transformation(s).
 * Fields containing filenames should be specified in the constructor. The
 * collection(s), transformation(s), and/or classifier(s) which contain those
 * filename fields should be provided in the endpoint connection specification
 * as values to the corresponding key.
 * <p>
 * This method will then perform its core action against all named fields found
 * in any of the named collections, transformations, and/or classifiers.
 * <p>
 * By default, lines are returned as records with the fields listed below. The
 * return field list can be optionally limited by passing in a list of IDs (as
 * strings) in the 'fields' parameter in the Endpoint Connection specification.
 * If the 'fields' parameter is omitted, these standard fields will be used for
 * Record creation. Extra fields listed that are not contained in those listed
 * below will be ignored.
 * <p>
 * <b>line</b> (integer): The zero-indexed line number that the record
 * was found of the given file.
 * <p>
 * <b>value</b> (string): The contents of the line.
 * <p>
 * <b>length</b> (integer): The length of the line value.
 * <p> 
 * <b>file</b> (string): The filename this record was found in.
 * <p>
 * <b>container-type</b> (string): What kind of container this record came from
 * (transformation, collection, classifier).
 * <p>
 * <b>container-id</b> (string): The name of the container this record came
 * from.
 * <p>
 * <p>
 * <i>Note: Files that cannot be opened or completely read are turned into
 * rejections. The reason for rejection will be based on the reason for the
 * inability to open the file.</i>
 * <p>
 * <p>
 * <b>Constructor Parameters:</b>
 * <p>
 * <i>The following are a list of currently accepted constructor parameters. In
 * the future, options for configuring this endpoint should be included in the
 * constructor parameters here.</i>
 * <p>
 * <b>file-fields</b> (String,List(String)): The name of the field containing
 * named files to read.
 * <p>
 * <i>Note: The field(s) named by this method should exist on the classifiers,
 * collections, and/or transformations listed in the specification. For every
 * classifer/collection/transformation listed, each named field will be treated
 * as containing the name of a file and this method will attempt to read them
 * into records.</i>
 * <p>
 * <p>
 * Example:
 * <p>
 * <p>
 * 
 * @author Ryan Berkheimer
 */
public class InMemoryFileReader extends BaseEndpoint implements IEndpoint {

    private List<String> fileFields = null;

    public InMemoryFileReader(Map<String, Object> parameters) {
        super(parameters);
        try {
            this.setFileFields(parameters.get("file-fields"));
        } catch (Exception e) {
            throw new IllegalArgumentException("Incorrect file fields were specified in the InMemoryFileReader.");
        }
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        DefaultPacket packet = new DefaultPacket();
        packet.addRecords(protocolRecord.getRecords());
        return packet;
    }

    /**
     * Returns the default fields for this endpoint. The default fields are
     * number, value, length, file, source-type, source-name
     */
    public List<IField> getDefaultFields() {
        List<IField> fields = new ArrayList<IField>();
        fields.add(new DefaultField("line", "integer", true, null, true));
        fields.add(new DefaultField("length", "integer", true, null, true));
        fields.add(new DefaultField("value", "string", true, null, true));
        fields.add(new DefaultField("file", "string", true, null, true));
        fields.add(new DefaultField("container-type", "string", true, null, true));
        fields.add(new DefaultField("container-id", "string", true, null, true));
        return fields;
    }

    public List<String> getFileFields() {
        return this.fileFields;
    }

    @SuppressWarnings("unchecked")
    private void setFileFields(Object fileFields) {
        if (fileFields instanceof String) {
            this.fileFields = new ArrayList<String>();
            this.fileFields.add((String) fileFields);
        } else if (fileFields instanceof List) {
            this.fileFields = ((List<Object>)fileFields).stream().map(ff -> (String) ff)
                    .collect(Collectors.toList());
            }
    }

}
