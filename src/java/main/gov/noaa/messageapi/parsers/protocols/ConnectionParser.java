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
public class ConnectionParser extends BaseParser {

    public ConnectionParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getConnectionMaps() {
        return (List<Map<String,Object>>) super.getValue("connections");
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("connections");
        return set;
    }


}
