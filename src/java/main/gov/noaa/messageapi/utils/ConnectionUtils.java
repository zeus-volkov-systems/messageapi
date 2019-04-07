package gov.noaa.messageapi.utils;

import java.util.List;

import gov.noaa.messageapi.interfaces.IConnection;
import gov.noaa.messageapi.interfaces.IProtocolRecord;
import gov.noaa.messageapi.interfaces.ISubmission;

import gov.noaa.messageapi.submissions.DefaultSubmission;

public class ConnectionUtils {

    public static ISubmission submitRecords(List<IConnection> connections, List<IProtocolRecord> recordSets) {
        return new DefaultSubmission();
    }

}
