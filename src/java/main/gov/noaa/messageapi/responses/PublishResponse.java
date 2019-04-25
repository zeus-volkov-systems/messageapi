package gov.noaa.messageapi.responses;

import java.util.List;
import java.util.stream.Collectors;
import java.util.concurrent.CompletableFuture;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IProtocol;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IResponse;
import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.responses.BaseResponse;
import gov.noaa.messageapi.requests.PublishRequest;

import gov.noaa.messageapi.utils.protocol.ConnectionUtils;
import gov.noaa.messageapi.utils.request.ContainerUtils;
import gov.noaa.messageapi.utils.request.ProtocolUtils;
import gov.noaa.messageapi.utils.request.PacketUtils;
import gov.noaa.messageapi.utils.general.ListUtils;


public class PublishResponse extends BaseResponse implements IResponse {

    public PublishResponse(PublishRequest request) {
        super(request);
        validate(this.request.getSchema(), this.request.getRecords())
                  .thenCompose(outgoingPacket -> this.factor(this.request.getContainer(), outgoingPacket))
                  .thenCompose(containerRecords -> this.prepare(this.request.getProtocol(), this.request.getContainer(), containerRecords))
                  .thenCompose(protocolRecords -> this.process(this.request.getProtocol().getConnections(), protocolRecords))
                  .thenCompose(incomingPacket -> this.resolve(incomingPacket))
                  .thenAccept(status -> this.setComplete(status));
    }

    /**
     * Async method that validates an input schema, returning an intermediate
     * future that will eventually yield a packet.
     * @param  schema  A schema containing the validation specification to apply to the records
     * @param  records A list of records to be validated against a specification
     * @return  A CompletableFuture representing the ongoing validation method (eventually yields a packet)
     */
    CompletableFuture<IPacket> validate(ISchema schema, List<IRecord> records) {
    	return CompletableFuture.supplyAsync(() -> {
    		IPacket packet = PacketUtils.create(this.request.getSchema(), this.request.getRecords());
            this.setRejections(packet.getRejections());
            return packet;
    	});
    }

    /**
     * Async method that containerizes(factors), a (validated) set of records against a container
     * specification, returning an intermediate future object that will eventually yield a
     * list of container records.
     * @param  container A container containing the factorization specification to apply to the records
     * @param  packet   A data packet containing records to be factored
     * @return           A CompletableFuture representing a factorization process that will eventually yield a list of container records
     */
    CompletableFuture<List<IContainerRecord>> factor(IContainer container, IPacket packet) {
    	return CompletableFuture.supplyAsync(() -> {
            return ContainerUtils.convertSchemaRecords(container,packet.getRecords());
    	});
    }

    /**
     * Async method that prepares a list of container records against a connection
     * specification provided by a protocol, returning an intermediate future object
     * that will eventually yield a list of protocol records.
     * @param  protocol A protocol containing the connection specifications
     * @param  records  A list of records to be prepared
     * @return          A CompletableFuture representing a protocol preparation process that will eventually yield a list of protocol records
     */
    CompletableFuture<List<IProtocolRecord>> prepare(IProtocol protocol, IContainer container, List<IContainerRecord> records) {
        return CompletableFuture.supplyAsync(() -> {
            return ProtocolUtils.convertContainerRecords(protocol, container, records);
        });
    }

    /**
     * Async method that processes protocol record sets using connections,
     * returning a packet
     * @param  connections [description]
     * @param  recordSets  [description]
     * @return             [description]
     */
    CompletableFuture<IPacket> process(List<IConnection> connections, List<IProtocolRecord> recordSets) {
        List<CompletableFuture<IPacket>> packetFutures = ListUtils.removeAllNulls(connections.stream().map(c -> {
            try {
                return ConnectionUtils.submitRecords(c, recordSets.stream().filter(r -> r.getConnection().equals(c.getId())).findFirst().get());
            } catch (Exception e) {
                System.out.println(e.getStackTrace());
                return null;
            }
        }).collect(Collectors.toList()));
        CompletableFuture<Void> allFutures = CompletableFuture.allOf(packetFutures.toArray(new CompletableFuture[packetFutures.size()]));
        CompletableFuture<List<IPacket>> allPacketFutures = allFutures.thenApply(v -> {
            return packetFutures.stream().map(packetFuture -> packetFuture.join()).collect(Collectors.toList());
        });
        return allPacketFutures.thenApply(allPackets ->{
            return PacketUtils.combineResults(allPackets);
        });
    }

    CompletableFuture<Boolean> resolve(IPacket packet) {
        return CompletableFuture.supplyAsync(() -> {
            //here we should do a protocol resolution based on the protocol/container/schema specs
            this.setRecords(packet.getRecords());
            this.getRejections().addAll(packet.getRejections());
            return true;
        });
    }


}
