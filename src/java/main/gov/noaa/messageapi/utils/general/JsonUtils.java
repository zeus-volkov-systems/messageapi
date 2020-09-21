package gov.noaa.messageapi.utils.general;

import java.io.FileReader;
import java.io.Reader;

import java.util.Set;
import java.util.Arrays;
import java.util.Iterator;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;


/**
 * This class contains static utilities that handle all manifest and parameter
 * configuration map JSON format parsing. There are two principal methods in this 
 * class that are mutually recursive to parse JSON arrays and maps into json.simple.JSONArray
 * and json.simple.JSONObject respectively. These are then returned as native Java Maps and Lists.
 * @author Ryan Berkheimer
 */
public class JsonUtils {

    protected final static JSONParser parser;

    static {
        parser = new JSONParser();
    }


    public static Reader read(final String resource) throws Exception {
        try {
            final Reader reader = new FileReader(resource);
            return reader;
        } catch (final Exception e) {
            System.err.println("Exception thrown while reading file: " + e.getMessage());
            return null;
        }
    }

    public static JSONObject parse(final String resource) throws Exception {
        try {
            final Reader jsonFile = read(resource);
            final Object jsonObj = parser.parse(jsonFile);
            jsonFile.close();
            return (JSONObject) jsonObj;
        } catch (final Exception e) {
            System.err.println("Exception thrown while parsing JSONObject: " + e.getMessage());
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    public static Set<String> keys(final JSONObject model) throws Exception {
        try {
            final Set<String> keySet = (Set<String>) model.keySet();
            return keySet;
        } catch (final Exception e) {
            System.err.println("Exception thrown while gathering keys: " + e.getMessage());
            return null;
        }
    }

    public static boolean hasKey(final JSONObject model, final String k) throws Exception {
        try {
            if (Arrays.asList(keys(model)).contains((Object) k)) {
                return true;
            }
            return false;
        } catch (final Exception e) {
            System.err.println("Exception thrown while testing has key: " + e.getMessage());
            return false;
        }
    }

    public static String getType(final JSONObject model, final String k) throws Exception {
        try {
            final Object v = model.get(k);
            return v.getClass().getName();
        } catch (final Exception e) {
            System.err.println("Exception thrown while getting the value type: " + e.getMessage());
            return null;
        }
    }

    public static Object get(final JSONObject model, final String k) {
        final Object v = model.get(k);
        return v;
    }

    public static HashMap<String, Object> convertObject(final JSONObject jsonObject) throws Exception {
        try {
            final HashMap<String, Object> objMap = new HashMap<String, Object>();
            final Set<String> keys = JsonUtils.keys(jsonObject);
            final Iterator<String> it = keys.iterator();
            while (it.hasNext()) {
                final String currKey = it.next();
                final Object currObj = JsonUtils.get(jsonObject, currKey);
                if (currObj instanceof JSONArray) {
                    objMap.put(currKey, (Object) convertArray((JSONArray) currObj));
                } else if (currObj instanceof JSONObject) {
                    objMap.put(currKey, (Object) convertObject((JSONObject) currObj));
                } else {
                    objMap.put(currKey, currObj);
                }
            }
            return objMap;
        } catch (final Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    public static List<Object> convertArray(final JSONArray jsonArray) throws Exception {
        try {
            final List<Object> arrays = new ArrayList<Object>();
            final Iterator<Object> it = jsonArray.iterator();
            while (it.hasNext()) {
                final Object currObj = it.next();
                if (currObj instanceof JSONArray) {
                    arrays.add((Object) convertArray((JSONArray) currObj));
                } else if (currObj instanceof JSONObject) {
                    arrays.add((Object) convertObject((JSONObject) currObj));
                } else {
                    arrays.add(currObj);
                }
            }
            return arrays;
        } catch (final Exception e) {
            e.printStackTrace();
            return null;
        }
    }


}
