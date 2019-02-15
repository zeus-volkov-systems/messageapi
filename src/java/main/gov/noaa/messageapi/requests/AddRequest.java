package gov.noaa.messageapi.requests;

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

public class AddRequest extends BaseRequest implements IRequest {

    public AddRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("add", schema, container, protocol);
    }

    public AddRequest(IRequest request) {
        super(request);
    }

    public AddRequest getCopy() {
        return new AddRequest(this);
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
        System.out.println("Container records...");
        containerRecords.stream().forEach(cR -> {
            cR.getFieldSets().stream().forEach(fS -> {
                System.out.println("Container Name: " + fS.getName());
                System.out.println("Container Namespace: " + fS.getName());
                System.out.println("...Fields...");
                fS.getFields().stream().forEach(f -> {
                    System.out.println(f.getName() + ": " + f.getValue());
                });
            });
        });
        return this.records;
    }

}
