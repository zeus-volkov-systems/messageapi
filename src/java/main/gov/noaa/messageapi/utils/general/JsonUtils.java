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


public class JsonUtils {

    protected final static JSONParser parser;

    static {
        parser = new JSONParser();
    }


    public static Reader read(String resource) throws Exception {
        try {
            Reader reader = new FileReader(resource);
            return reader;
        } catch (Exception e) {
            System.err.println("Exception thrown while reading file: " + e.getMessage());
            return null;
        }
    }


    public static JSONObject parse(String resource) throws Exception {
        try {
            Reader jsonFile = read(resource);
            Object jsonObj = parser.parse(jsonFile);
            jsonFile.close();
            return (JSONObject) jsonObj;
        } catch (Exception e) {
            System.err.println("Exception thrown while parsing JSONObject: " + e.getMessage());
            return null;
        }
    }


    @SuppressWarnings("unchecked")
    public static Set<String> keys(JSONObject model) throws Exception {
        try {
            Set<String> keySet = (Set<String>) model.keySet();
            return keySet;
        } catch (Exception e) {
            System.err.println("Exception thrown while gathering keys: " + e.getMessage());
            return null;
        }
    }


    public static boolean hasKey(JSONObject model, String k) throws Exception {
        try {
            if (Arrays.asList(keys(model)).contains(k)) {
                return true;
            }
            return false;
        } catch (Exception e) {
            System.err.println("Exception thrown while testing has key: " + e.getMessage());
            return false;
        }
    }


    public static String getType(JSONObject model, String k) throws Exception {
        try {
            Object v = model.get(k);
            return v.getClass().getName();
        } catch (Exception e){
            System.err.println("Exception thrown while getting the value type: " + e.getMessage());
            return null;
        }
    }

    public static Object get(JSONObject model, String k) {
        Object v = model.get(k);
        return v;
    }

    public static HashMap<String, Object> convertObject(JSONObject jsonObject) throws Exception {
        try {
            HashMap<String, Object> objMap = new HashMap<String, Object>();
            Set<String> keys = JsonUtils.keys(jsonObject);
            Iterator<String> it = keys.iterator();
            while (it.hasNext()) {
                String currKey = it.next();
                Object currObj = JsonUtils.get(jsonObject, currKey);
                String objType = currObj.getClass().getName();
                if (objType.contains("JSONArray")) {
                    objMap.put(currKey, (Object) convertArray((JSONArray) currObj));
                } else if (objType.contains("JSONObject")){
                    objMap.put(currKey, (Object) convertObject((JSONObject) currObj));
                } else {
                    objMap.put(currKey, currObj);
                }
            }
            return objMap;
        } catch (Exception e){
            System.err.println("Exception thrown while converting the object: " + e.getMessage());
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    public static List<Object> convertArray(JSONArray jsonArray) throws Exception {
        try {
            List<Object> arrays = new ArrayList<Object>();
            Iterator<Object> it = jsonArray.iterator();
            while (it.hasNext()) {
                Object currObj = it.next();
                String objType = currObj.getClass().getName();
                if (objType.contains("JSONArray")) {
                    arrays.add((Object) convertArray((JSONArray) currObj));
                } else if (objType.contains("JSONObject")){
                    arrays.add((Object) convertObject((JSONObject) currObj));
                } else {
                    arrays.add(currObj);
                }
            }
            return arrays;
        } catch (Exception e) {
            System.err.println("Exception thrown while converting the array: " + e.getMessage());
            return null;
        }
    }


}
