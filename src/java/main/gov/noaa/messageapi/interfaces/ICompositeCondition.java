package gov.noaa.messageapi.interfaces;

import java.util.List;

public interface ICompositeCondition extends ICondition {

    public List<String> getConditions();

}
