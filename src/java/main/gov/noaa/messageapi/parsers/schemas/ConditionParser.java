package gov.noaa.messageapi.parsers.schemas;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * @author Ryan Berkheimer
 */
public class ConditionParser extends BaseParser {

    public ConditionParser(final String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getConditionMaps() {
        return (List<Map<String, Object>>) super.getValue("conditions");
    }

    public void process() {
    }

    public Set<String> getRequiredKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("conditions");
        return set;
    }


}
