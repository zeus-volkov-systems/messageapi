package gov.noaa.messageapi.utils.general;

import java.util.Map;
import java.util.List;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.stream.Collectors;


/**
 * This class contains static, idempotent utilities for manipulation and analysis
 * of generic (abstracted) java maps.
 * @author Ryan Berkheimer
 */
public class MapUtils {

    /**
     * Merges a list of maps of arbitrary K/V type into a new single map that contains
     * all keys/values from each map in turn. this method uses putAll and traverses the list
     * in order, so new values will overwrite old (if the key already existed on the new map).
     * @param  list A list of maps to merge
     * @return      A new map with all keys from all maps merged
     */
    public static <K,V> Map<K,V> mergeMapList(final List<Map<K, V>> list) {
        final Map<K, V> mergedMap = new HashMap<K, V>();
        list.stream().forEach(item -> {
            mergedMap.putAll(item);
        });
        return mergedMap;
    }

    /**
     * Merges a list of maps into a single map. If a key overlaps between maps, that
     * key is added to the merged map with all original values in a list.
     * 
     * @param list A list of maps to merge
     * @return A map with all keys of all input maps, and all their values combined.
     */
    public static <K, V> Map<K, List<V>> mergeMapsMergeValues(final List<Map<K, V>> list) {
        final List<K> allKeys = ListUtils.eliminateDuplicates(ListUtils.flatten(
                list.stream().map(m -> m.keySet()).map(s -> new ArrayList<K>(s)).collect(Collectors.toList())));
        return MapUtils.mergeMapList(allKeys.stream().map(key -> {
            final List<V> valueList = list.stream().filter(m -> m.containsKey(key)).map(m -> m.get(key))
                    .collect(Collectors.toList());
            final Map<K, List<V>> mergedValMap = new HashMap<K, List<V>>();
            mergedValMap.put(key, valueList);
            return mergedValMap;
        }).collect(Collectors.toList()));
    }

    public static <K, V> Map<K, List<V>> flattenValues(final Map<K, List<List<V>>> map) {
        return MapUtils.mergeMapList(map.entrySet().stream().map(e -> {
            final Map<K, List<V>> mergedValsMap = new HashMap<K, List<V>>();
            final List<V> vals = new ArrayList<V>();
            e.getValue().stream().forEach(v -> v.stream().forEach(va -> vals.add(va)));
            mergedValsMap.put(e.getKey(), vals);
            return mergedValsMap;
        }).collect(Collectors.toList()));
    }


}
