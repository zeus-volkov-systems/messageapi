package gov.noaa.messageapi.parsers.containers;

import java.util.Map;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.AbstractMap;
import java.util.stream.Collectors;

import gov.noaa.messageapi.parsers.BaseParser;
import gov.noaa.messageapi.utils.general.ListUtils;
import gov.noaa.messageapi.utils.general.PathUtils;

/**
 * This class handles general collection map parsing (collections being part of the container layer).
 * Currently, collection assembly can be performed using a path-as-string to the file containing a JSON map with
 * a 'collections' key. The file pointed to by the path should contain a JSON map with a top-level 'collections' key
 * that itself corresponds to a list of collections, each containing a required id, required array of field ids, 
 * optional map of classifiers, and optional array of condition ids.
 * @author Ryan Berkheimer
 */
public class CollectionParser extends BaseParser {

    public CollectionParser(final String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getCollectionMaps() {
        return (List<Map<String, Object>>) super.getValue("collections");
    }

    public List<String> getCollections() {
        return getCollectionMaps().stream().map(cMap -> (String) cMap.get("id")).collect(Collectors.toList());
    }

    @SuppressWarnings("unchecked")
    public List<Map.Entry<String, String>> getClassifiers() {
        return ListUtils.eliminateDuplicates(
                ListUtils.removeAllNulls(ListUtils.flatten(getCollectionMaps().stream().map(cMap -> {
                    if (cMap.containsKey("classifiers")) {
                        return this.parseClassifierMap((Map<String, Object>) cMap.get("classifiers"));
                    }
                    return new ArrayList<Map.Entry<String, String>>();
                }).collect(Collectors.toList()))));
    }

    @SuppressWarnings("unchecked")
    private List<Map.Entry<String, String>> parseClassifierMap(final Map<String, Object> classifierMap) {
        final List<Map.Entry<String, String>> returnList = new ArrayList<Map.Entry<String, String>>();
        classifierMap.entrySet().stream().forEach(e -> {
            if (e.getValue() instanceof List) {
                final List<Map.Entry<String, String>> entries = this.parseClassifierList(e.getKey(),
                        (List<String>) e.getValue());
                entries.forEach(entry -> returnList.add(entry));
            } else {
                returnList.add(new AbstractMap.SimpleEntry<String, String>(e.getKey(), (String) e.getValue()));
            }
        });
        return returnList;
    }

    private List<Map.Entry<String, String>> parseClassifierList(final String key, final List<String> vals) {
        return vals.stream().map(val -> {
            return new AbstractMap.SimpleEntry<String, String>(key, val);
        }).collect(Collectors.toList());
    }

    public void process() {
    }

    public Set<String> getRequiredKeys() {
        final Set<String> set = new HashSet<String>();
        set.add("collections");
        return set;
    }

}
