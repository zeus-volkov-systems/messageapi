package gov.noaa.messageapi.utils.containers;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gov.noaa.messageapi.interfaces.ITransformation;
import gov.noaa.messageapi.transformations.DefaultTransformation;
import gov.noaa.messageapi.utils.general.ListUtils;

public class TransformationUtils {

    public static List<ITransformation> buildTransformations(List<Map<String,Object>> transformationMaps) {
        return transformationMaps.stream().map(r -> {
            return new DefaultTransformation(r);
        }).collect(Collectors.toList());
    }

    public static List<String> getReferences(List<ITransformation> transformations) {
        return ListUtils.flatten(transformations.stream().map(r -> {
            List<String> transformationReferences = new ArrayList<String>();
            transformationReferences.add(r.getParent());
            transformationReferences.add(r.getChild());
            return transformationReferences;
        }).collect(Collectors.toList()));
    }

    public static List<String> getReferences(ITransformation transformation) {
        List<String> transformationReferences = new ArrayList<String>();
        transformationReferences.add(transformation.getParent());
        transformationReferences.add(transformation.getChild());
        return transformationReferences;
    }

    public static List<ITransformation> getReferencedTransformations(List<ITransformation> transformations, List<String> referencedNames) {
        return transformations.stream().filter(transformation -> {
            if (referencedNames.contains(transformation.getId())) {
                return true;
            }
            return false;
        }).collect(Collectors.toList());
    }

    public static List<ITransformation> getUnreferencedTransformations(List<ITransformation> transformations, List<String> referencedNames) {
        return transformations.stream().filter(transformation -> {
            if (referencedNames.contains(transformation.getId())) {
                return false;
            }
            return true;
        }).collect(Collectors.toList());
    }

}
