package gov.noaa.messageapi.test.endpoints;

import java.util.Map;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.packets.DefaultPacket;

public class EmailEndpointTest implements IEndpoint {

    public EmailEndpointTest(Map<String,Object> parameters) {}

    public IPacket process(IProtocolRecord record) {
        DefaultPacket packet = new DefaultPacket();
        packet.addRecords(record.getRecords());
        return packet;
    }

}
