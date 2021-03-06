package gov.noaa.messageapi.parsers.protocols;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * @author Ryan Berkheimer
 */
public class EndpointParser extends BaseParser {

    public EndpointParser(final String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getEndpointMaps() {
        return (List<Map<String, Object>>) super.getValue("endpoints");
    }

    public void process() {
    }

    public Set<String> getRequiredKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("endpoints");
        return set;
    }


}
