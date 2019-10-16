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

struct string_vector
{
    int count;
    int max_length;
    char** strings;
};

struct classifier
{
    char* key;
    char* val;
};