package gov.noaa.messageapi.utils.general;

import java.io.File;
import java.util.List;
import java.util.ArrayList;

import gov.noaa.messageapi.utils.general.EnvUtils;

public class PathUtils {

    private static String replaceLast(String string, String toReplace, String replacement) {
        int pos = string.lastIndexOf(toReplace);
        if (pos > -1) {
            return string.substring(0, pos)
                + replacement
                + string.substring(pos + toReplace.length(), string.length());
        } else {
            return string;
        }
    }

    /**
     * This method expands the {} special character found in strings that are read during parsing.
     * This method is not durable but it works on current OSX Darwin and both Redhat and Ubuntu Linuxes.
     * If there is a better, more general way of finding the root project directory, the method business logic should
     * be replaced by that.
     * @param  path The path containing a {} character to be replaced by the relative package path.
     * @return      Returns the path with {} replaced by the package path.
     */
    public static String reconcileKeywords(String path) {
        File jarDir = new File(ClassLoader.getSystemClassLoader().getResource(".").getPath());
        String replaceTest;
        String replaceMain;
        String returnPath;
        switch (EnvUtils.getOS()) {
            case "osx":
                replaceTest = replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                replaceMain = replaceLast(replaceTest, "/classes/java/main", "");
                returnPath = path.replace("{}", replaceMain);
                return returnPath;
            case "unix":
                replaceTest = replaceLast(jarDir.getAbsolutePath(), "/classes/test", "");
                replaceMain = replaceLast(replaceTest, "/classes/main", "");
                returnPath = path.replace("{}", replaceMain);
                return returnPath;
            default:
                replaceTest = replaceLast(jarDir.getAbsolutePath(), "/classes/test", "");
                replaceMain = replaceLast(replaceTest, "/classes/main", "");
                returnPath = path.replace("{}", replaceMain);
                return returnPath;
        }
    }

    public static List<String> reconcileKeywords(List<String> paths) {
        List<String> l = new ArrayList<String>();
        for (String path: paths) {
            l.add(reconcileKeywords(path));
        }
        return l;
    }

}
