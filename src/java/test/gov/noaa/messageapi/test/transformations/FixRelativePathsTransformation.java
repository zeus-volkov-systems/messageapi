package gov.noaa.messageapi.test.transformations;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.general.PathUtils;


/**
 * <h1>FixRelativePathsTransformation</h1>
 * <p>
 * This Transformation will return a list of
 * records for every record in the <b>transform-key</b> container. The new list
 * of records will have any paths specified in the <b>fields</b> set for this
 * transformation updated with the relative path keyword ({}) replaced with the
 * package path. This transformation is useful in file operation tests or using
 * package-internal/relative resources.
 * <p>
 * <i>Note - this uses a string method, so fields must be string-castable.</i>
 *
 * @author Ryan Berkheimer
 */
public class FixRelativePathsTransformation implements ITransformation {

    private List<String> relativePathFields = null;
    private String transformKey = null;

    public FixRelativePathsTransformation(List<String> fields, Map<String, Object> params) {
        this.setRelativePathFields(fields);
        this.setTransformKey((String) params.get("transform-key"));
    }

    public List<IRecord> process(Map<String, List<IRecord>> transformationMap) {
        return ListUtils.removeAllNulls(transformationMap.get(this.getTransformKey()).stream().map(record -> {
                this.getRelativePathFields().stream().forEach(field -> {
                    record.setField(field, PathUtils.reconcileKeywords((String) record.getField(field).getValue()));
                });
                return record;
            }).collect(Collectors.toList()));
    }

    private void setRelativePathFields(List<String> fields) {
        this.relativePathFields = fields;
    }

    private List<String> getRelativePathFields() {
        return this.relativePathFields;
    }

    private void setTransformKey(String transformKey) {
        this.transformKey = transformKey;
    }

    private String getTransformKey() {
        return this.transformKey;
    }

}