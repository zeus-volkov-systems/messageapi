#include <jni.h>

/**
 * @author Ryan Berkheimer
 */

struct field_value
{
    jobject jvalue;
};

struct field
{
    jobject jfield;
};

struct field_list
{
    int count;
    struct field **fields;
};

struct record
{
    jobject jrecord;
};

struct record_list
{
    int count;
    //struct record **records;
    jobject jrecords;
};


struct string_list
{
    int count;
    int max_length;
    char **strings;
};

struct classifier
{
    char* key;
    char* val;
};