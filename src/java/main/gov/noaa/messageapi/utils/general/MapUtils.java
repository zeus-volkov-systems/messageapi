package gov.noaa.messageapi.utils.general;

import java.util.HashMap;
import java.util.Map;
import java.util.List;

public class MapUtils {

    /**
     * Merges a list of maps of arbitrary K/V type into a new single map that contains
     * all keys/values from each map in turn. this method uses putAll and traverses the list
     * in order, so new values will overwrite old (if the key already existed on the new map).
     * @param  list A list of maps to merge
     * @return      A new map with all keys from all maps merged
     */
    public static <K,V> Map<K,V> mergeMapList(List<Map<K,V>> list) {
        Map<K,V> mergedMap = new HashMap<K,V>();
        list.stream().forEach(item -> {
            mergedMap.putAll(item);
        });
        return mergedMap;
    }

}
