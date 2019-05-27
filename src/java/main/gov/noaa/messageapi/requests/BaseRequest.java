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

import gov.noaa.messageapi.utils.schema.ConditionUtils;


/**
 * BaseRequest serves as a base class for Requests, holding common behaviors
 * to all requests, handling the initialization and access of type, schema,
 * container, protocol, records, and request record. Different user requests
 * may extend this BaseRequest, implementing the IRequest, in order to
 * modify or extend this basic behavior expected of all requests.
 * @author Ryan Berkheimer
 */
public class BaseRequest {

    private String type;
    protected ISchema schema;
    protected IContainer container;
    protected IProtocol protocol;
    protected List<IRecord> records;
    private IRecord requestRecord;

    public BaseRequest(String type, ISchema schema, IContainer container,
                        IProtocol protocol) {
        this.setType(type);
        this.setSchema(schema);
        this.setContainer(container);
        this.setProtocol(protocol);
        this.initializeRecords();
        this.setRequestRecord(this.getSchema());
    }

    public BaseRequest(IRequest request) {
        this.setType(request.getType());
        this.setSchema(request.getSchema());
        this.setContainer(request.getContainer());
        this.setProtocol(request.getProtocol());
        this.setRecords(request.getRecords());
        this.setRequestRecord(request.getSchema());

    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public IRecord createRecord() {
        IRecord r = this.schema.createRecord();
        this.records.add(ConditionUtils.nullifyConditions(r));
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

    public IRecord getRequestRecord() {
        return this.requestRecord;
    }

    public void setCondition(String conditionId, Object value) {
        this.getRequestRecord().setCondition(conditionId, value);
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

    private void setRequestRecord(ISchema schema) {
        IRecord r = schema.createRecord();
        this.requestRecord = r;
    }

}
