package gov.noaa.messageapi.responses;

import java.util.Arrays;
import java.util.List;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IRejection;


/**
 * @author Ryan Berkheimer
 */
public class BaseResponse {

    protected IRequest request = null;
    private List<IRejection> rejections = null;
    private List<IRecord> records = null;
    private boolean complete = false;

    public BaseResponse(IRequest request) {
        this.setRequest(request);
        this.setComplete(false);
    }

    public List<IRejection> getRejections() {
        return this.rejections;
    }

    public List<IRecord> getRecords() {
        return this.records;
    }

    public IRequest getRequest() {
        return this.request;
    }

    public Boolean isComplete() {
        return this.complete;
    }

    public void setRecords(List<IRecord> records) {
        this.records = records;
    }

    public void setRejections(List<IRejection> rejections) {
        this.rejections = rejections;
    }

    public void setComplete(Boolean complete) {
        this.complete = complete;
    }

    private void setRequest(IRequest request) {
        this.request = request.getCopy(Arrays.asList("records"));
    }

}
