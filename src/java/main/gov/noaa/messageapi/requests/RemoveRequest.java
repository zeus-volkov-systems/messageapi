package gov.noaa.messageapi.requests;

import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

public class RemoveRequest extends BaseRequest implements IRequest {

    public RemoveRequest(ISchema schema, IContainer container, IProtocol protocol) {
        super("remove", schema, container, protocol);
    }

    public RemoveRequest(IRequest request) {
        super(request);
    }

    public RemoveRequest getCopy() {
        return new RemoveRequest(this);
    }

    public List<IRecord> process() {
        return this.records;
    }

    public List<IRejection> prepare() {
        return new ArrayList<IRejection>();
    }

    public List<IRejection> analyzeSchema() {
        return new ArrayList<IRejection>();
    }

    public void prepareSchema(List<IRejection> rejections) {
    }

}
