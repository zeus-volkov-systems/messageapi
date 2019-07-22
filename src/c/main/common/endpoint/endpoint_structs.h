#include <jni.h>

/**
 * name: record vector
 * contents:
 * count (integer) - how many records there are
 * records (records pointer) - 
 * 
 * 
 * @author Ryan Berkheimer
 */

struct records_vector
{
    int count;
    jobject** records;
};