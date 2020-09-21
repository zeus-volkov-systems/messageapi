package gov.noaa.messageapi.exceptions;

import java.lang.Exception;

public class MessageApiException extends Exception {

    /**
     *
     */
    private static final long serialVersionUID = -4783565590470822212L;

    /**
     * Required (generated) serial version ID for serializable class
     */

    public MessageApiException(final String message, final Throwable err) {
        super(message, err);
    }

    public MessageApiException(final String message) {
        super(message);
    }


}
