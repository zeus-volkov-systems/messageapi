package gov.noaa.messageapi.utils.general;

import java.util.Objects;
import java.util.List;
import java.util.Collection;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;


/**
 * @author Ryan Berkheimer
 */
public class ListUtils {

    /**
     * Helper method used to eliminate duplicate values from a list.
     * @param  list The list for which duplicates may exist
     * @return      The input list as a list of a set
     */
    public static <T> List<T> eliminateDuplicates(List<T> list) {
        return list.stream().distinct().collect(Collectors.toList());
    }

    /**
     * Flattens a collection of lists into a single flat list.
     * @param  collection The collection of lists to flatten
     * @return      A flat list created from all the comcollectioned elements of the nested input list.
     */
    public static <T> List<T> flatten(Collection<List<T>> collection) {
        return collection.stream().flatMap(Collection::stream).collect(Collectors.toList());
    }

    /**
     * Checks a list, returning true if all elements are null.
     * @param  array The array to check for nulls.
     * @return       true if all elements are null, false if there are any non-null elements.
     */
    public static boolean isAllNulls(Iterable<?> array) {
        return StreamSupport.stream(array.spliterator(), true).allMatch(o -> o == null);
    }

    /**
     * Returns a new list, removing all null elements from the list.
     * @param  list The input list possibly containing nulls
     * @return      The new list, same as old list with any nulls filtered out.
     */
    public static <T> List<T> removeAllNulls(List<T> list) {
        return list.stream().filter(Objects::nonNull).collect(Collectors.toList());
    }

    /**
     * Returns true if list (collection) is null or empty.
     * @param  c The list to check
     * @return   true if list is null/empty
     */
    public static boolean isNullOrEmpty( final Collection< ? > c ) {
    return c == null || c.isEmpty();
    }

}
