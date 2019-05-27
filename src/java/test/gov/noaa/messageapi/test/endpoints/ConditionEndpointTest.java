package gov.noaa.messageapi.test.endpoints;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.packets.DefaultPacket;

/**
 * @author Ryan Berkheimer
 */
public class ConditionEndpointTest implements IEndpoint {

    public ConditionEndpointTest(Map<String,Object> parameters) {
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        DefaultPacket packet = new DefaultPacket();
        return packet;
    }

}
