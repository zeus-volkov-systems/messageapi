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
public class FieldParser extends BaseParser {

    public FieldParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getFieldMaps() {
        return (List<Map<String,Object>>) super.getValue("fields");
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("fields");
        return set;
    }


}
