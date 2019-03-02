package gov.noaa.messageapi.requests;

import gov.noaa.messageapi.utils.request.ProtocolUtils;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.requests.BaseRequest;
import gov.noaa.messageapi.utils.request.SchemaUtils;
import gov.noaa.messageapi.utils.request.ContainerUtils;
import gov.noaa.messageapi.utils.request.RejectionUtils;
import gov.noaa.messageapi.utils.general.ListUtils;

public class PublishRequest extends BaseRequest implements IRequest {

    public PublishRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("publisher", schema, container, protocol);
    }

    public PublishRequest(IRequest request) {
        super(request);
    }

    public PublishRequest getCopy() {
        return new PublishRequest(this);
    }

    public List<IRejection> prepare() {
        List<IRejection> requiredFieldRejections = RejectionUtils.getRequiredFieldRejections(this.getRecords());
        this.setRecords(SchemaUtils.filterRejections(this.getRecords(), requiredFieldRejections));
        this.setRecords(SchemaUtils.filterNonValuedFields(this.getRecords()));
        this.setRecords(SchemaUtils.filterNonValuedConditions(this.getRecords()));
        this.setRecords(SchemaUtils.filterFieldlessConditions(this.getRecords()));
        List<IRejection> fieldConditionRejections = RejectionUtils.getFieldConditionRejections(this.getSchema(), this.getRecords());
        this.setRecords(SchemaUtils.filterRejections(this.getRecords(), fieldConditionRejections));
        List<IRejection> allRejections = ListUtils.flatten(new ArrayList<List<IRejection>>(Arrays.asList(requiredFieldRejections, fieldConditionRejections)));
        return allRejections;
    }

    public List<IRecord> process() {
        List<IContainerRecord> containerRecords = ContainerUtils.convertSchemaRecords(this.getContainer(), this.getRecords());
        ProtocolUtils.convertContainerRecords(this.getProtocol(), containerRecords);
        return this.records;
    }

}
