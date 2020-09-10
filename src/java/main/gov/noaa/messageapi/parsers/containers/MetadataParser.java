package gov.noaa.messageapi.parsers.containers;

import java.util.Map;
import java.util.Set;
import java.util.HashSet;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * This class handles general metadata map parsing (metadata being part of the container layer).
 * Currently, metadata assembly can be performed using a path-as-string to the file containing a JSON map with
 * a 'metadata' key pointing to a map. Metadata maps can contain key-value pairs of anything - they are accessible from the session
 * after creation by accessing the session container interface and then the container definition, then
 * using the getMetadata method.
 * 
 * @author Ryan Berkheimer
 */
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
