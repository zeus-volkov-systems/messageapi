package gov.noaa.messageapi.utils.protocol;

import java.util.concurrent.CompletableFuture;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IPacket;

import gov.noaa.messageapi.packets.DefaultPacket;

public class ConnectionUtils {

    public static CompletableFuture<IPacket> submitRecords(IConnection connection, IProtocolRecord record) {
        return CompletableFuture.supplyAsync(() -> {
            return new DefaultPacket();
        });
    }

}
