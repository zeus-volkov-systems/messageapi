package gov.noaa.messageapi.test.endpoints;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.packets.DefaultPacket;

public class ConditionEndpointTest implements IEndpoint {

    public ConditionEndpointTest(Map<String,Object> parameters) {
    }

    public DefaultPacket process(IProtocolRecord protocolRecord) {
        DefaultPacket packet = new DefaultPacket();
        return packet;
    }

}
