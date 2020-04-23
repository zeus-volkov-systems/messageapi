package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

/**
 * @author Ryan Berkheimer
 */
public interface ITransformation {

    public List<IRecord> process(Map<String,List<IRecord>> transformationMap);

}
