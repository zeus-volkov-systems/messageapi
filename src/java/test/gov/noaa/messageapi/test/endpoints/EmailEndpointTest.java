package gov.noaa.messageapi.test.endpoints;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.interfaces.IEndpoint;
import gov.noaa.messageapi.interfaces.IField;
import gov.noaa.messageapi.interfaces.IPacket;
import gov.noaa.messageapi.interfaces.IProtocolRecord;

import gov.noaa.messageapi.packets.DefaultPacket;
import gov.noaa.messageapi.endpoints.BaseEndpoint;


/**
 * @author Ryan Berkheimer
 */
public class EmailEndpointTest extends BaseEndpoint implements IEndpoint {

    public EmailEndpointTest(Map<String,Object> parameters) {
        super(parameters);
    }

    public IPacket process(IProtocolRecord protocolRecord) {
        protocolRecord.getRecordsByTransformation("join-test");
        DefaultPacket packet = new DefaultPacket();
        packet.addRecords(protocolRecord.getRecords());
        return packet;
    }

    public List<IField> getDefaultFields() {
        return new ArrayList<IField>();
    }

}
