package gov.noaa.messageapi.parsers;

import java.util.HashMap;
import java.util.Set;

import gov.noaa.messageapi.utils.general.JsonUtils;

import org.json.simple.JSONObject;

/**
 * @author Ryan Berkheimer
 */
public abstract class BaseParser {

    protected JSONObject jsonModel;
    protected HashMap<String, Object> parsedModel;
    protected Set<String> keys;

    public BaseParser(final String resource) throws Exception {
        try {
            jsonModel = JsonUtils.parse(resource);
            update();
        } catch (final Exception e) {
            System.err.println("Exception thrown in resource string constructor: " + e.getMessage());
            System.exit(1);
        }
    }

    public BaseParser() {
    }

    @SuppressWarnings("unchecked")
    public BaseParser(final Object jsonModel) throws Exception {
        try {
            this.jsonModel = null;
            this.parsedModel = (HashMap<String, Object>) jsonModel;
            keys = this.parsedModel.keySet();
            if (isValid()) {
                process();
            }
        } catch (final Exception e) {
            System.err.println("Exception thrown in resource hashmap constructor: " + e.getMessage());
            System.exit(1);
        }
    }

    public abstract Set<String> getRequiredKeys();

    public abstract void process() throws Exception;

    protected void getKeys() throws Exception {
        try {
            keys = JsonUtils.keys(jsonModel);
        } catch (final Exception e) {
            System.err.println("Exception thrown while gathering resource keys: " + e.getMessage());
            System.exit(1);
        }
    }

    protected Boolean hasKey(final String k) {
        return parsedModel.containsKey(k);
    }

    protected Object getValue(final String k) {
        return parsedModel.get(k);
    }

    protected void setValue(final String k, final Object v) {
        parsedModel.put(k, v);
    }

    private boolean isValid() {
        final Set<String> requiredKeys = getRequiredKeys();
        if (keys.containsAll(requiredKeys)) {
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
        } catch (final Exception e) {
            System.err.println("Exception thrown while updating the resource: " + e.getMessage());
            System.exit(1);
        }
    }


}
