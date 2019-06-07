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

    public TransformationParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getTransformationMaps() {
        return (List<Map<String,Object>>) super.getValue("transformations");
    }

    public List<String> getTransformations() {
        return getTransformationMaps().stream().map(tMap -> (String)tMap.get("id")).collect(Collectors.toList());
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("transformations");
        return set;
    }


}
