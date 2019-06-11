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
        this.copySchema(schema);
        this.copyContainer(container);
        this.copyProtocol(protocol);
        this.initializeRecords();
        this.setRequestRecord(this.getSchema());
    }

    /**
     * Standard constructor from request - default is to deep copy everything.
     */
    public BaseRequest(IRequest request) {
        this.setType(request.getType());
        this.copySchema(request.getSchema());
        this.copyContainer(request.getContainer());
        this.copyProtocol(request.getProtocol());
        this.copyRecords(request.getRecords());
        this.setRequestRecord(request.getSchema());
    }

    /**
     * Allows specification of a list of named components that will be deep-copied on constructor.
     * Allowed values are 'schema', 'container', 'protocol', 'records'
     * @param request
     * @param copyComponents
     */
    public BaseRequest(IRequest request, List<String> copyComponents) {
        this.setType(request.getType());
        if (copyComponents.contains("schema")) {
            this.copySchema(request.getSchema());
        } else {
            this.setSchema(request.getSchema());
        }
        if (copyComponents.contains("container")) {
            this.copyContainer(request.getContainer());
        } else {
            this.setContainer(request.getContainer());
        }
        if (copyComponents.contains("protocol")) {
            this.copyProtocol(request.getProtocol());
        } else {
            this.setProtocol(request.getProtocol());
        }
        if (copyComponents.contains("records")) {
            this.copyRecords(request.getRecords());
        } else {
            this.setRecords(request.getRecords());
        }
        this.setRequestRecord(this.getSchema());

    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    /**
     * Creates a new record in a request, making sure the conditions are null,
     * and returns it for update by the user.
     * @return A new IRecord belonging to the request records collection
     */
    public IRecord createRecord() {
        IRecord r = this.schema.createRecord();
        this.records.add(ConditionUtils.nullifyComparisonConditions(r));
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

    private void copySchema(ISchema schema) {
        this.schema = (ISchema) schema.getCopy();
    }

    private void copyContainer(IContainer container) {
        this.container = (IContainer) container.getCopy();
    }

    private void copyProtocol(IProtocol protocol) {
        this.protocol = (IProtocol) protocol.getCopy();
    }

    protected void copyRecords(List<IRecord> records) {
        this.records = Collections.synchronizedList(records.stream().map(r -> r.getCopy()).collect(Collectors.toList()));
    }

    private void setSchema(ISchema schema) {
        this.schema = schema;
    }

    private void setContainer(IContainer container) {
        this.container = container;
    }

    private void setProtocol(IProtocol protocol) {
        this.protocol = protocol;
    }

    public void setRecords(List<IRecord> records) {
        this.records = records;
    }

    private void setRequestRecord(ISchema schema) {
        IRecord r = schema.createRecord();
        this.requestRecord = r;
    }

}
