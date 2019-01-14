package gov.noaa.messageapi.parsers.schemas;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

public class MetadataParser extends BaseParser {

    public MetadataParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public Map<String, Object> getMetadataMap() {
        return (Map<String,Object>) super.getValue("metadata");
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("metadata");
        return set;
    }


}
