package gov.noaa.messageapi.utils.general;


/**
 * This class contains static utilities for evaluation of environmental issues. It is not
 * critical to the MessageAPI core package but is used in parsing relative paths for the
 * relative path transformation. It may be removed at some point if the relative path mechanism
 * is modified.
 * @author Ryan Berkheimer
 */
public class EnvUtils {

    public static String getOS(){
        final String OS = System.getProperty("os.name").toLowerCase();
        if (isWindows(OS)) {
            return "windows";
        } else if (isMac(OS)) {
            return "osx";
        } else if (isUnix(OS)) {
            return "unix";
        } else if (isSolaris(OS)) {
            return "solaris";
        } else {
            return null;
        }
    }

    private static boolean isWindows(final String OS) {
        return (OS.indexOf("win") >= 0);
    }

    private static boolean isMac(final String OS) {
        return (OS.indexOf("mac") >= 0);
    }

    private static boolean isUnix(final String OS) {
        return (OS.indexOf("nix") >= 0 || OS.indexOf("nux") >= 0 || OS.indexOf("aix") > 0);
    }

    private static boolean isSolaris(final String OS) {
        return (OS.indexOf("sunos") >= 0);
    }

}
