package gov.noaa.messageapi.test.transformations;

import java.util.Map;
import java.util.List;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.IRecord;
import gov.noaa.messageapi.interfaces.ITransformation;

import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.general.PathUtils;
import gov.noaa.messageapi.utils.general.StringUtils;

import gov.noaa.messageapi.transformations.BaseTransformation;


/**
 * <h1>FixRelativePathsTransformation</h1> <b>Description:</b>
 * <p>
 * This Transformation will return a list of records for every record in the
 * <b>transform-key</b> container. The new list of records will have any paths
 * specified in the <b>fields</b> set for this transformation updated with the
 * relative path keyword (defaults to '{}') replaced with a different string
 * (options described below). By default, the keyword is replaced by the root
 * path of where the code is being executed (so, if in a JAR, the root of the
 * JAR.)
 * <p>
 * <p>
 * <h2>Configuration Parameters</h2> <b>transform-key</b>(required) (String):
 * The name of the transformation-container containing records having fields
 * that have relative paths to be transformed. For example, if a transformation
 * has a specified container "records": {"file-collection": {"COLLECTION":
 * "coll-1"}}, the "file-collection" container record set could be specified.
 * <p>
 * <b>fields</b> (required) (List(String)): A list of strings that specify
 * container fields to be transformed. E.g., using the example container above,
 * if coll-1 had fields with paths desired to be expanded called "dir-path-1"
 * and "dir-path-2", then this parameter would be specified as "fields":
 * ["dir-path-1", "dir-path-2"]
 * <p>
 * <b>substitution-keyword</b> (optional) (String): A substring that will be substituted in the field value.
 * Defaults to {}.
 * <p>
 * <p>
 * <b>substitution-string</b> (optional) (String): A substring that will replace the keyword. If not specified,
 * defaults to package root of running resource.
 * <p>
 * <p>
 * <b>substitution-field</b> (optional) (String): A field that has a value that will be used in substitution.
 * If not specified, defaults to package root of running resource.
 * <p>
 * 
 * <i>Note - this uses a string method, so fields (specified above) must be
 * string-castable.</i>
 * <p>
 * <i>Note - if both substitution-string and substitution-field are specified, the substitution-string takes precedence.</i>
 *
 * @author Ryan Berkheimer
 */
public class FixRelativePathsTransformation extends BaseTransformation implements ITransformation {

    private List<String> relativePathFields = null;
    private String transformKey = null;
    private String substitutionKeyword = "{}";
    private String substitutionString = null;
    private String substitutionField = null;

    @SuppressWarnings("unchecked")
    public FixRelativePathsTransformation(Map<String, Object> params) {
        super(params);
        try {
            this.setRelativePathFields((List<String>) params.get("fields"));
            this.setTransformKey((String) params.get("transform-key"));
        } catch (Exception e) {
            System.err.println("Fix Relative Paths Transformation is missing a required field. Check your params map.");
            System.exit(1);
        }
        this.setSubstitutionKeyword(params);
        this.setSubstitutionString(params);
        this.setSubstitutionField(params);
    }

    public List<IRecord> process(Map<String, List<IRecord>> transformationMap) {
        return ListUtils.removeAllNulls(transformationMap.get(this.getTransformKey()).stream().map(record -> {
                this.getRelativePathFields().stream().forEach(field -> {
                    if (this.getSubstitutionString() != null) {
                        record.setField(field, StringUtils.replaceLast((String) record.getField(field).getValue(), this.getSubstitutionKeyword(),
                            this.getSubstitutionString()));
                    } else if (this.getSubstitutionField() != null) {
                        record.setField(field, StringUtils.replaceLast((String) record.getField(field).getValue(), this.getSubstitutionKeyword(),
                            this.getSubstitutionField()));
                    } else {
                        record.setField(field, PathUtils.reconcileKeywords((String) record.getField(field).getValue(), this.getSubstitutionKeyword()));
                    }
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

    private void setSubstitutionKeyword(Map<String, Object> parameters) {
        if (parameters.containsKey("substitution-keyword")) {
            this.substitutionKeyword = (String) parameters.get("substitution-keyword");
        }
    }

    private void setSubstitutionString(Map<String, Object> parameters) {
        if (parameters.containsKey("substitution-string")) {
            this.substitutionString = (String) parameters.get("substitution-string");
        }
    }

    private void setSubstitutionField(Map<String, Object> parameters) {
        if (parameters.containsKey("substitution-field")) {
            this.substitutionField = (String) parameters.get("substitution-field");
        }
    }

    private String getTransformKey() {
        return this.transformKey;
    }

    private String getSubstitutionKeyword() {
        return this.substitutionKeyword;
    }

    private String getSubstitutionString() {
        return this.substitutionString;
    }

    private String getSubstitutionField() {
        return this.substitutionField;
    }

}
