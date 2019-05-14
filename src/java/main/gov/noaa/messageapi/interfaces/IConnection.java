package gov.noaa.messageapi.interfaces;

import java.util.Map;
import java.util.List;

import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

public interface IConnection {

    public String getId();
    public List<String> getCollections();
    public  Map<String,List<Object>> getClassifiers();
    public Map<String, Map<String,Object>> getTransformationMap();
    public List<Object> getClassiferValues(String classifierKey);
    public String getEndpointClass();
    public Map<String,Object> getEndpointConstructor();
    public IPacket process(IProtocolRecord record);
    public IConnection getCopy();

}
