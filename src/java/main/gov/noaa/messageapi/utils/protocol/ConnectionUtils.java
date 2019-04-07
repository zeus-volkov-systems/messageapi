package gov.noaa.messageapi.utils.protocol;

import java.util.List;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IPacket;

import gov.noaa.messageapi.packets.DefaultPacket;

public class ConnectionUtils {

    public static IPacket submitRecords(List<IConnection> connections, List<IProtocolRecord> recordSets) {
        return new DefaultPacket();
    }

}
