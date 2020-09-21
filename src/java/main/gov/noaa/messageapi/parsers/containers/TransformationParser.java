package gov.noaa.messageapi.parsers.containers;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.stream.Collectors;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * @author Ryan Berkheimer
 */
public class TransformationParser extends BaseParser {

    private List<Map<String,Object>> transformationMaps;

    @SuppressWarnings("unchecked")
    public TransformationParser(final String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
        this.setTransformationMaps((List<Map<String, Object>>) super.getValue("transformations"));
    }

    public TransformationParser(final List<Map<String, Object>> transformationMapList) throws Exception {
        this.setTransformationMaps(transformationMapList);
    }

    public List<Map<String, Object>> getTransformationMaps() {
        return this.transformationMaps;
    }

    public List<String> getTransformations() {
        return getTransformationMaps().stream().map(tMap -> (String) tMap.get("id")).collect(Collectors.toList());
    }

    public void process() {
    }

    private void setTransformationMaps(final List<Map<String, Object>> transformationMapList) {
        this.transformationMaps = transformationMapList;
    }

    public Set<String> getRequiredKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("transformations");
        return set;
    }


}
