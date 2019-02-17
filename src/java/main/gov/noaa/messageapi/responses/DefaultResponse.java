package gov.noaa.messageapi.responses;

import java.util.concurrent.CompletableFuture;

import gov.noaa.messageapi.interfaces.IRequest;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.responses.BaseResponse;

public class DefaultResponse extends BaseResponse implements IResponse {

    public DefaultResponse(IRequest request) {
        super(request);
        CompletableFuture.supplyAsync(() -> this.request.prepare())
            .thenAccept(rejections -> setRejections(rejections))
                .thenRun(() ->
                    CompletableFuture.supplyAsync(() -> this.request.process())
                .thenAccept(records -> setRecords(records)))
                    .thenRun(() ->
                        setComplete(true));
    }

}
