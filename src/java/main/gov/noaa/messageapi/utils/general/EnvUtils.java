package gov.noaa.messageapi.utils.general;


/**
 * @author Ryan Berkheimer
 */
public class EnvUtils {

    public static String getOS(){
        String OS = System.getProperty("os.name").toLowerCase();
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

    private static boolean isWindows(String OS){
    return (OS.indexOf("win") >= 0);
    }

    private static boolean isMac(String OS){
        return (OS.indexOf("mac") >= 0);
    }

    private static boolean isUnix(String OS) {
        return (OS.indexOf("nix") >= 0 || OS.indexOf("nux") >= 0 || OS.indexOf("aix") > 0 );
    }

    private static boolean isSolaris(String OS) {
        return (OS.indexOf("sunos") >= 0);
    }

}
