package gov.noaa.messageapi.utils.general;

import java.io.File;
import java.util.List;
import java.util.ArrayList;


/**
 * This class contains static utilities for path manipulation.
 * This class primarily exists to facilitate keyword reconciliation.
 * It was used heavily for development, and may deprecate in a future release.
 * @author Ryan Berkheimer
 */
public class PathUtils {

    /**
     * This method expands the {} special character found in strings that are read during parsing.
     * This method is not durable but it works on current OSX Darwin and both Redhat and Ubuntu Linuxes.
     * If there is a better, more general way of finding the root project directory, the method business logic should
     * be replaced by that.
     * Note - gradle updated their build in the 5 series so that Linux and Unix have the same structure for their 'build' directory.
     * This method has changed to accommodate that. As it is gradle dependent, if the build system changes,
     * this method should be reverified and/or replaced.
     * @param  path The path containing a {} character to be replaced by the relative package path.
     * @return      Returns the path with {} replaced by the package path.
     */
    public static String reconcileKeywords(final String path) {
        if (path.contains("{}")) {
            final File jarDir = new File(ClassLoader.getSystemClassLoader().getResource(".").getPath());
            String replaceTest;
            String replaceMain;
            String returnPath;
            switch (EnvUtils.getOS()) {
                case "osx":
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace("{}", replaceMain);
                    return returnPath;
                case "unix":
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace("{}", replaceMain);
                    return returnPath;
                default:
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace("{}", replaceMain);
                    return returnPath;
            }
        } else {
            return path;
        }
    }

    public static String reconcileKeywords(final String path, final String keyword) {
        if (path.contains(keyword)) {
            final File jarDir = new File(ClassLoader.getSystemClassLoader().getResource(".").getPath());
            String replaceTest;
            String replaceMain;
            String returnPath;
            switch (EnvUtils.getOS()) {
                case "osx":
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace(keyword, replaceMain);
                    return returnPath;
                case "unix":
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace(keyword, replaceMain);
                    return returnPath;
                default:
                    replaceTest = StringUtils.replaceLast(jarDir.getAbsolutePath(), "/classes/java/test", "");
                    replaceMain = StringUtils.replaceLast(replaceTest, "/classes/java/main", "");
                    returnPath = path.replace(keyword, replaceMain);
                    return returnPath;
            }
        } else {
            return path;
        }
    }

    public static List<String> reconcileKeywords(final List<String> paths) {
        final List<String> l = new ArrayList<String>();
        for (final String path : paths) {
            l.add(reconcileKeywords(path));
        }
        return l;
    }

}
