package gov.noaa.messageapi.parsers.containers;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

public class RelationshipParser extends BaseParser {

    public RelationshipParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getRelationshipMaps() {
        return (List<Map<String,Object>>) super.getValue("relationships");
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("relationships");
        return set;
    }


}
