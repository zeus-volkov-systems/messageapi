package gov.noaa.messageapi.utils.request;

import java.util.List;

import gov.noaa.messageapi.interfaces.IContainerRecord;
import gov.noaa.messageapi.interfaces.IProtocol;

public class ProtocolUtils {

    /**
     * Converts a set of schema records to container records according to the specified container.
     * This involves first creating a record blueprint based on the container definition (which contains
     * field sets (called field units), and relationship sets (called relationship units), and then
     * duplicating the record blueprint for every schema record and copying values from those fields
     * to any matching field unit.
     * @param  container The container containing definitions of field units and relationship units
     * @param  records   The schema records to be converted to container records
     * @return           A list of container records
     */
    public static void convertContainerRecords(IProtocol protocol, List<IContainerRecord> containerRecords) {
        protocol.process(containerRecords);
    }

}
