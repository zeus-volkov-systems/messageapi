package gov.noaa.messageapi.interfaces;

import java.util.List;
import gov.noaa.messageapi.interfaces.ICondition;

/**
 * @author Ryan Berkheimer
 */
public interface ICompositeCondition extends ICondition {

    public List<String> getConditions();

}
