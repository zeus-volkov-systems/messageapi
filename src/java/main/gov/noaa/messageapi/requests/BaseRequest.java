package gov.noaa.messageapi.requests;

import java.util.stream.Collectors;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IRecord;

public class BaseRequest {

    private String type;
    protected ISchema schema;
    protected IContainer container;
    protected IProtocol protocol;
    protected List<IRecord> records;

    public BaseRequest(String type, ISchema schema, IContainer container,
                        IProtocol protocol) {
        setType(type);
        setSchema(schema);
        setContainer(container);
        setProtocol(protocol);
        initializeRecords();
    }

    public BaseRequest(IRequest request) {
        setType(request.getType());
        setSchema(request.getSchema());
        setContainer(request.getContainer());
        setProtocol(request.getProtocol());
        setRecords(request.getRecords());
    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public IRecord createRecord() {
        IRecord r = this.schema.createRecord();
        this.records.add(r);
        return r;
    }

    public String getType() {
        return this.type;
    }

    public ISchema getSchema() {
        return this.schema;
    }

    public IContainer getContainer() {
        return this.container;
    }

    public IProtocol getProtocol() {
        return this.protocol;
    }

    private void initializeRecords() {
        this.records = Collections.synchronizedList(new ArrayList<IRecord>());
    }

    private void setType(String type) {
        this.type = type;
    }

    private void setSchema(ISchema schema) {
        this.schema = (ISchema) schema.getCopy();
    }

    private void setContainer(IContainer container) {
        this.container = (IContainer) container.getCopy();
    }

    private void setProtocol(IProtocol protocol) {
        this.protocol = (IProtocol) protocol.getCopy();
    }

    protected void setRecords(List<IRecord> records) {
        this.records = Collections.synchronizedList(records.stream().map(r -> r.getCopy()).collect(Collectors.toList()));
    }

}
