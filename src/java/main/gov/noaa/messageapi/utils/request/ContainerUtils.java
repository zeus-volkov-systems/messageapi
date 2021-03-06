package gov.noaa.messageapi.utils.request;

import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ISchema;
import gov.noaa.messageapi.interfaces.IContainer;
import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ICollection;
import gov.noaa.messageapi.interfaces.IContainerRecord;

import gov.noaa.messageapi.records.container.ContainerRecord;

import gov.noaa.messageapi.utils.containers.CollectionUtils;


/**
 * This class contains static utilities for creating, parsing, or otherwise manipulating
 * containers. Containers are record collections and include collections, transformations,
 * and classifiers.
 * @author Ryan Berkheimer
 */
public class ContainerUtils {

    /**
     * Converts a set of schema records to container records according to the specified container.
     * This involves first creating a record blueprint based on the container definition (which contains
     * field sets (called field units), and transformation sets (called transformation units), and then
     * duplicating the record blueprint for every schema record and copying values from those fields
     * to any matching field unit.
     * @param  container The container containing definitions of field units and transformation units
     * @param  records   The schema records to be converted to container records
     * @return           A list of container records
     */
    public static List<IContainerRecord> convertSchemaRecords(final ISchema schema, final IContainer container,
            final IRecord requestRecord, final List<IRecord> schemaRecords) {
        final IContainerRecord containerRecordTemplate = createRecordTemplate(container);
        return schemaRecords.stream().map(schemaRecord -> {
            final IContainerRecord containerRecord = CollectionUtils.setFieldValues(containerRecordTemplate.getCopy(),
                    schemaRecord.getFields());
            return CollectionUtils.validateCollectionConditions(schema, containerRecord, requestRecord);
        }).collect(Collectors.toList());
    }

    /**
     * Converts a set of schema records to container records according to the
     * specified container IN PARALLEL. This involves first creating a record blueprint based on
     * the container definition (which contains field sets (called field units), and
     * transformation sets (called transformation units), and then duplicating the
     * record blueprint for every schema record and copying values from those fields
     * to any matching field unit. Uses the parallelStreams mechanism to do the conversion.
     * 
     * @param container The container containing definitions of field units and
     *                  transformation units
     * @param records   The schema records to be converted to container records
     * @return A list of container records
     */
    public static List<IContainerRecord> convertSchemaRecordsInParallel(final ISchema schema, final IContainer container,
            final IRecord requestRecord, final List<IRecord> schemaRecords) {
        final IContainerRecord containerRecordTemplate = createRecordTemplate(container);
        return schemaRecords.parallelStream().map(schemaRecord -> {
            final IContainerRecord containerRecord = CollectionUtils.setFieldValues(containerRecordTemplate.getCopy(),
                    schemaRecord.getFields());
            return CollectionUtils.validateCollectionConditions(schema, containerRecord, requestRecord);
        }).collect(Collectors.toList());
    }

    /**
     * Creates an empty record for use in record conversion by copy. Uses the
     * definition of the provided container to create a new empty record object,
     * with
     * 
     * @param container The container containing a definition that the template
     *                  ContainerRecord object will be based on
     * @return A new, empty,
     */
    public static IContainerRecord createRecordTemplate(final IContainer container) {
        final List<ICollection> collections = CollectionUtils
                .buildCollections(container.getDefinition().getCollectionMaps());
        return new ContainerRecord(collections);
    }

}
