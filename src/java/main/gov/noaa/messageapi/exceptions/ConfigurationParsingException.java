package gov.noaa.messageapi.exceptions;

public class ConfigurationParsingException extends MessageApiException {

    /**
     * Required (generated) serial version ID for serializable class
     */
    private static final long serialVersionUID = 6896902577211242022L;

    public ConfigurationParsingException(final String message, final Throwable err) {
        super(message, err);
    }

    public ConfigurationParsingException(final String message) {
        super(message);
    }


}
