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

import gov.noaa.messageapi.requests.ParallelRequest;

import gov.noaa.messageapi.utils.protocol.ConnectionUtils;
import gov.noaa.messageapi.utils.request.ContainerUtils;
import gov.noaa.messageapi.utils.request.ProtocolUtils;
import gov.noaa.messageapi.utils.request.PacketUtils;
import gov.noaa.messageapi.utils.general.ListUtils;


/**
 * A ParallelResponse is the main processing unit of Parallel System Publishing.
 * Parallel Responses operate on Parallel Requests, which are the fundamental
 * containers and work specifications of Parallel System Publishing.
 * ParallelResponses work in a procedurally stereotyped manner - requests are
 * validated, factored, prepared, processed, resolved, and then marked as completed,
 * in that order. Each of these stages is run in an internally-asynchronous manner,
 * which allows for parallelization on an intra-stage level. On an inter-stage level,
 * they are dependent on each other in a procedural manner.
 * @author Ryan Berkheimer
 */
public class ParallelResponse extends BaseResponse implements IResponse {

    /**
     * The default constructor for a parallel publish response. When a response is created
     * using this constructor, all processing is performed immediately on the provided
     * request - in order, these steps are -validation, factoring, preparation, processing,
     * and resolution.
     * @param request A request containing records to process and resolve in the response.
     */
    public ParallelResponse(final ParallelRequest request) {
        super(request);
        this.validate(this.request.getSchema(), this.request.getRecords())
                .thenCompose(outgoingPacket -> this.factor(this.request.getSchema(), this.request.getContainer(),
                        this.request.getRequestRecord(), outgoingPacket))
                .thenCompose(containerRecords -> this.prepare(this.request.getProtocol(), containerRecords))
                .thenCompose(
                        protocolRecords -> this.process(this.request.getProtocol().getConnections(), protocolRecords))
                .thenCompose(incomingPacket -> this.resolve(incomingPacket))
                .thenAccept(status -> this.setComplete(status));
    }

    /**
     * Async method that validates an input schema, returning an intermediate future
     * that will eventually yield a packet.
     * 
     * @param schema  A schema containing the validation specification to apply to
     *                the records
     * @param records A list of records to be validated against a specification
     * @return A CompletableFuture representing the ongoing validation method
     *         (eventually yields a packet)
     */
    CompletableFuture<IPacket> validate(final ISchema schema, final List<IRecord> records) {
        return CompletableFuture.supplyAsync(() -> {
            final IPacket packet = PacketUtils.create(this.request.getSchema(), this.request.getRecords());
            this.setRejections(packet.getRejections());
            return packet;
        });
    }

    /**
     * Async method that containerizes(factors), a (validated) set of records
     * against a container specification, returning an intermediate future object
     * that will eventually yield a list of container records.
     * 
     * @param container A container containing the factorization specification to
     *                  apply to the records
     * @param packet    A data packet containing records to be factored
     * @return A CompletableFuture representing a factorization process that will
     *         eventually yield a list of container records
     */
    CompletableFuture<List<IContainerRecord>> factor(final ISchema schema, final IContainer container,
            final IRecord requestRecord, final IPacket packet) {
        return CompletableFuture.supplyAsync(() -> {
            return ContainerUtils.convertSchemaRecords(schema, container, requestRecord, packet.getRecords());
        });
    }

    /**
     * Async method that prepares a list of container records against a connection
     * specification provided by a protocol, returning an intermediate future object
     * that will eventually yield a list of protocol records.
     * 
     * @param protocol A protocol containing the connection specifications
     * @param records  A list of container records to be converted/doled out to
     *                 protocol records
     * @return A CompletableFuture representing a protocol preparation process that
     *         will eventually yield a list of protocol records
     */
    CompletableFuture<List<IProtocolRecord>> prepare(final IProtocol protocol, final List<IContainerRecord> records) {
        return CompletableFuture.supplyAsync(() -> {
            return ProtocolUtils.convertContainerRecords(protocol, records);
        });
    }

    /**
     * Async method that processes protocol record sets using connections, returning
     * a packet
     * 
     * @param connections A list of connections that will be matched to and process
     *                    record sets.
     * @param recordSets  A list of protocol records to process in an associated
     *                    connection (each protocol record contains a set of
     *                    records).
     * @return returns a CompletableFuture that eventaully resolves to a data
     *         packet, containing the combined results from all connection data
     *         processing.
     */
    CompletableFuture<IPacket> process(final List<IConnection> connections, final List<IProtocolRecord> recordSets) {
        final List<CompletableFuture<IPacket>> packetFutures = ListUtils.removeAllNulls(connections.parallelStream().map(c -> {
            try {
                return ConnectionUtils.submitRecords(c,
                        recordSets.parallelStream().filter(r -> r.getConnectionId().equals(c.getId())).findFirst().get());
            } catch (final Exception e) {
                System.out.println(e.getStackTrace());
                System.exit(1);
                return null;
            }
        }).collect(Collectors.toList()));
        final CompletableFuture<Void> allFutures = CompletableFuture
                .allOf(packetFutures.toArray(new CompletableFuture[packetFutures.size()]));
        final CompletableFuture<List<IPacket>> allPacketFutures = allFutures.thenApply(v -> {
            return packetFutures.parallelStream().map(packetFuture -> packetFuture.join()).collect(Collectors.toList());
        });
        return allPacketFutures.thenApply(allPackets -> {
            return PacketUtils.combineResults(allPackets);
        });
    }

    /**
     * Resolves a data packet by setting the response records equal to the combined
     * records and rejections contained in the packet that was put together out of
     * data retrieved from the protocol layer.
     * 
     * @param packet A data packet containing records and rejections compiled from
     *               the protocol layer
     * @return Returns a completable future that contains (true) when the operation
     *         is complete
     */
    CompletableFuture<Boolean> resolve(final IPacket packet) {
        return CompletableFuture.supplyAsync(() -> {
            this.setRecords(packet.getRecords());
            this.getRejections().addAll(packet.getRejections());
            return true;
        });
    }

}
