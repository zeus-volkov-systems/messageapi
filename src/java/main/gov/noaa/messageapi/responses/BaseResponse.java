package gov.noaa.messageapi.responses;

import java.util.List;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;

public class BaseResponse {

    protected IRequest request = null;
    private List<IRejection> rejections = null;
    private List<IRecord> records = null;
    private boolean complete = false;

    public BaseResponse(IRequest request) {
        setRequest(request);
        setComplete(false);
    }

    public List<IRejection> getRejections() {
        return this.rejections;
    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public boolean isComplete() {
        return this.complete;
    }

    protected void setRecords(List<IRecord> records) {
        this.records = records;
    }

    protected void setRejections(List<IRejection> rejections) {
        this.rejections = rejections;
    }

    protected void setComplete(boolean complete) {
        this.complete = complete;
    }

    private void setRequest(IRequest request) {
        this.request = request.getCopy();
    }

}
