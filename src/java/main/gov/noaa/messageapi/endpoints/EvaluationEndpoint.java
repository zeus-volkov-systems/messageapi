package gov.noaa.messageapi.endpoints;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.packets.DefaultPacket;
import gov.noaa.messageapi.utils.general.ListUtils;

/**
 * <h1>Evaluation Endpoint</h1>
 * This endpoint provides a passthrough mechanism for returning
 * any containers specified in the configuration to the caller.
 * This endpoint allows use of arbitrary collections, classifications, and/or transformations
 * to be returned as a single record set.
 * <p>
 * To use this Endpoint, the user should add any Collections, Classifiers,
 * and/or Transformations to the Endpoint Connection map that are desired to be
 * included in the Record List passed back in the return DataPacket.
 *
 * There are no constructor parameters used by this method. It will only call any
 * collection(s), classifier(s), or transformation(s) specified on the input map.
 *
 * @author Ryan Berkheimer
 */
public class EvaluationEndpoint extends BaseEndpoint implements IEndpoint {

    public EvaluationEndpoint(final Map<String, Object> parameters) {
        super(parameters);
    }

    /**
     * Default processing method for the evaluation endpoint. This method will
     * gather any and all records for any and all collections, classifiers, and/or
     * transformations attached to the associated connection map.
     * 
     * @param protocolRecord The protocolRecord for this endpoint connection - holds
     *                       all containers
     * @return A unified record set for all containers associated with the endpoint
     *         connection
     */
    public IPacket process(final IProtocolRecord protocolRecord) {
        final DefaultPacket packet = new DefaultPacket();
        try {
            final List<IRecord> collectionRecords = this.processCollections(protocolRecord);
            packet.addRecords(collectionRecords);
            final List<IRecord> classifierRecords = this.processClassifiers(protocolRecord);
            packet.addRecords(classifierRecords);
            final List<IRecord> transformationRecords = this.processTransformations(protocolRecord);
            packet.addRecords(transformationRecords);
        } catch (final Exception e) {
            return null;
        }
        return packet;
    }

    /**
     * For every collection specified in the Connection map, retrieves records from
     * the protocol record.
     * 
     * @param protocolRecord The protocolRecord associated with the endpoint
     *                       connection
     * @return The list of records (minus nulls) for all collections referenced in
     *         the endpoint connection
     */
    private List<IRecord> processCollections(final IProtocolRecord protocolRecord) {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getCollections().stream().map(collId -> {
            return protocolRecord.getRecordsByCollection(collId);
        }).collect(Collectors.toList())));
    }

    /**
     * For every classifier entry specified in the Connection map, retrieves records
     * from the protocol record.
     * 
     * @param protocolRecord The protocolRecord associated with the endpoint
     *                       connection
     * @return The list of records (minus nulls) for all classifiers referenced in
     *         the endpoint connection
     */
    private List<IRecord> processClassifiers(final IProtocolRecord protocolRecord) {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getClassifiers().stream().map(entry -> {
            return protocolRecord.getRecordsByClassifier(entry.getKey(), entry.getValue());
        }).collect(Collectors.toList())));
    }

    /**
     * For every transformation specified in the Connection map, retrieves records
     * from the protocol record.
     * 
     * @param protocolRecord The protocolRecord associated with the endpoint
     *                       connection
     * @return The list of records (minus nulls) for all transformations referenced
     *         in the endpoint connection
     */
    private List<IRecord> processTransformations(final IProtocolRecord protocolRecord) {
        return ListUtils.removeAllNulls(ListUtils.flatten(this.getTransformations().stream().map(transId -> {
            return protocolRecord.getRecordsByTransformation(transId);
        }).collect(Collectors.toList())));
    }

    /**
     * Returns the default fields for this endpoint. The default fields are number,
     * value, length, file, container-type, container-name
     */
    public List<IField> getDefaultFields() {
        final List<IField> fields = new ArrayList<IField>();
        return fields;
    }


}
