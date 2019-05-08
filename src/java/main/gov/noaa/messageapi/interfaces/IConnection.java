package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IConnection {

    public String getId();
    public List<String> getCollections();
    public  Map<String,List<Object>> getClassifiers();
    public List<String> getTransformations();
    public List<Object> getClassiferValues(String classifierKey);
    public IPacket process(IProtocolRecord record);

}
