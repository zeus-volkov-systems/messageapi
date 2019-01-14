package gov.noaa.messageapi.parsers;

import java.util.HashMap;
import java.util.Set;

import gov.noaa.messageapi.utils.general.JsonUtils;

import org.json.simple.JSONObject;


public abstract class BaseParser {

    protected JSONObject jsonModel;
    protected HashMap<String, Object> parsedModel;
    protected Set<String> keys;

    public BaseParser(String resource) throws Exception {
        try {
            jsonModel = JsonUtils.parse(resource);
            update();
        } catch (Exception e) {
            System.err.println("Exception thrown in resource string constructor: " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    public BaseParser(Object jsonModel) throws Exception {
        try {
            this.jsonModel = null;
            this.parsedModel = (HashMap<String, Object>) jsonModel;
            keys = this.parsedModel.keySet();
            if (isValid()) {
                process();
            }
        } catch (Exception e) {
            System.err.println("Exception thrown in resource hashmap constructor: " + e.getMessage());
        }
    }

    public abstract Set<String> getRequiredKeys();
    public abstract void process() throws Exception;

    protected void getKeys() throws Exception {
        try {
            keys = JsonUtils.keys(jsonModel);
        } catch (Exception e){
            System.err.println("Exception thrown while gathering resource keys: " + e.getMessage());
        }
    }

    protected Boolean hasKey(String k) {
        return parsedModel.containsKey(k);
    }

    protected Object getValue(String k) {
        return parsedModel.get(k);
    }

    protected void setValue(String k, Object v) {
        parsedModel.put(k, v);
    }

    private boolean isValid() {
        Set<String> requiredKeys = getRequiredKeys();
        if (keys.containsAll(requiredKeys)){
            return true;
        }
        return false;
    }

    public void update() throws Exception {
        try {
            getKeys();
            if (isValid()) {
                parsedModel = JsonUtils.convertObject(jsonModel);
                process();
            }
        } catch (Exception e) {
            System.err.println("Exception thrown while updating the resource: " + e.getMessage());
        }
    }


}
