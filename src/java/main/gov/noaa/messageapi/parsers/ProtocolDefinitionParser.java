package gov.noaa.messageapi.parsers;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

public class ProtocolDefinitionParser extends BaseParser {

    public ProtocolDefinitionParser(String spec) throws Exception {
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
        set.add("type");
        set.add("connections");
        return set;
    }


}
