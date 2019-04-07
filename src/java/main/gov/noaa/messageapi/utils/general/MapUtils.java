package gov.noaa.messageapi.utils.general;

import java.util.HashMap;
import java.util.Map;
import java.util.List;

public class MapUtils {

    public static <K,V> Map<K,V> mergeMapList(List<Map<K,V>> list) {
        Map<K,V> mergedMap = new HashMap<K,V>();
        list.stream().forEach(item -> {
            mergedMap.putAll(item);
        });
        return mergedMap;
    }

}
