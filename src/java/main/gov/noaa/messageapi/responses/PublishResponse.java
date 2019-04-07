package gov.noaa.messageapi.responses;

import java.util.List;
import java.util.concurrent.CompletableFuture;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.ISubmission;
import gov.noaa.messageapi.interfaces.IConnection;

import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.responses.BaseResponse;
import gov.noaa.messageapi.requests.PublishRequest;

import gov.noaa.messageapi.utils.SubmissionUtils;
import gov.noaa.messageapi.utils.ConnectionUtils;
import gov.noaa.messageapi.utils.request.ContainerUtils;
import gov.noaa.messageapi.utils.request.ProtocolUtils;


public class PublishResponse extends BaseResponse implements IResponse {

    public PublishResponse(PublishRequest request) {
        super(request);
        validate(this.request.getSchema(), this.request.getRecords())
                  .thenCompose(outgoingSubmission -> this.factor(this.request.getContainer(), outgoingSubmission.getRecords()))
                  .thenCompose(containerRecords -> this.prepare(this.request.getProtocol(), containerRecords))
                  .thenCompose(protocolRecords -> this.process(this.request.getProtocol().getConnections(), protocolRecords))
                  //.thenCompose(incomingSubmission -> this.resolve(, processedRecords))
                  .thenAccept(status -> this.setComplete(true));
    }

    /**
     * Async method that validates an input schema, returning an intermediate
     * submission object with validated records and rejections.
     * @param  schema  The schema attached to the session that created the request
     * @param  records
     * @return
     */
    CompletableFuture<ISubmission> validate(ISchema schema, List<IRecord> records) {
    	return CompletableFuture.supplyAsync(() -> {
    		ISubmission submission = SubmissionUtils.create(this.request.getSchema(), this.request.getRecords());
            this.setRejections(submission.getRejections());
            return submission;
    	});
    }

    CompletableFuture<List<IContainerRecord>> factor(IContainer container, List<IRecord> records) {
    	return CompletableFuture.supplyAsync(() -> {
            return ContainerUtils.convertSchemaRecords(container,records);
    	});
    }

    CompletableFuture<List<IProtocolRecord>> prepare(IProtocol protocol, List<IContainerRecord> records) {
        return CompletableFuture.supplyAsync(() -> {
            return ProtocolUtils.convertContainerRecords(protocol, records);
        });
    }

    CompletableFuture<ISubmission> process(List<IConnection> connections, List<IProtocolRecord> recordSets) {
        return CompletableFuture.supplyAsync(() -> {
            return ConnectionUtils.submitRecords(connections, recordSets);
        });
    }

    /*CompletableFuture<List<IProtocolRecord>> resolve(List<IRecord> records, List<IRejection> rejections ,List<IProtocolRecord> protocolRecords) {
        return CompletableFuture.supplyAsync(() -> {
            return ProtocolUtils.
        });
    }*/


}
