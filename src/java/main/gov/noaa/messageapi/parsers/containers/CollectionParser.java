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
 * @author Ryan Berkheimer
 */
public class CollectionParser extends BaseParser {

    public CollectionParser(String spec) throws Exception {
        super(PathUtils.reconcileKeywords(spec));
    }

    @SuppressWarnings("unchecked")
    public List<Map<String, Object>> getCollectionMaps() {
        return (List<Map<String,Object>>) super.getValue("collections");
    }

    public List<String> getCollections() {
        return getCollectionMaps().stream().map(cMap -> (String)cMap.get("id")).collect(Collectors.toList());
    }

    @SuppressWarnings("unchecked")
    public List<Map.Entry<String,String>> getClassifiers() {
        return ListUtils.removeAllNulls(ListUtils.flatten(getCollectionMaps().stream().map(cMap -> {
            if (cMap.containsKey("classifiers")) {
                return this.parseClassifierMap((Map<String,Object>) cMap.get("classifiers"));
            }
            return null;
        }).collect(Collectors.toList())));
    }

    @SuppressWarnings("unchecked")
    private List<Map.Entry<String,String>> parseClassifierMap(Map<String,Object> classifierMap) {
        List<Map.Entry<String,String>> returnList = new ArrayList<Map.Entry<String,String>>();
        classifierMap.entrySet().stream().forEach(e -> {
            if (e.getValue() instanceof List) {
                List<Map.Entry<String,String>> entries = this.parseClassifierList(e.getKey(), (List<String>)e.getValue());
                entries.forEach(entry->returnList.add(entry));
            } else {
                returnList.add(new AbstractMap.SimpleEntry<String, String>(e.getKey(), (String)e.getValue()));
            }
        });
        return returnList;
    }

    private List<Map.Entry<String,String>> parseClassifierList(String key, List<String> vals) {
        return vals.stream().map(val -> {
            return new AbstractMap.SimpleEntry<String, String>(key, val);
        }).collect(Collectors.toList());
    }

    public void process(){
    }

    public Set<String> getRequiredKeys() {
        Set<String> set = new HashSet<String>();
        set.add("collections");
        return set;
    }

}
