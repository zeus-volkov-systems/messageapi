package gov.noaa.messageapi.utils.general;


/**
 * This class contains static, idempotent utilties for common string manipulations.
 * @author Ryan Berkheimer
 */
public class StringUtils {

    /**
     * Replaces the last occurance of the specified target substring with the specified replacement substring
     * within the specified string. If there is no occurance, just returns the original string.
     */
    public static String replaceLast(final String string, final String toReplace, final String replacement) {
        final int pos = string.lastIndexOf(toReplace);
        if (pos > -1) {
            return string.substring(0, pos)
                + replacement
                + string.substring(pos + toReplace.length(), string.length());
        } else {
            return string;
        }
    }

}
