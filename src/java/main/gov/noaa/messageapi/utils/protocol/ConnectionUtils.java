package gov.noaa.messageapi.utils.protocol;

import java.util.concurrent.CompletableFuture;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.IPacket;

public class ConnectionUtils {

    public static CompletableFuture<IPacket> submitRecords(IConnection connection, IProtocolRecord record) {
        if (record != null) {
            return CompletableFuture.supplyAsync(() -> {
                return connection.process(record);
            });
        }
        return null;
    }

}
