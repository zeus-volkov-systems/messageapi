
#ifndef _Included_messageapi_structs
#define _Included_messageapi_structs

#include <jni.h>

/**
 * @author Ryan Berkheimer
 */

struct list_item
{
    jobject jitem;
};

struct val_list
{
    int count;
    jobject jlist;
};

struct session
{
    jobject jsession;
};

struct response
{
    jobject jresponse;
};

struct request
{
    jobject jrequest;
};

struct condition
{
    jobject jcondition;
};

struct condition_list
{
    int count;
    struct condition **conditions;
};
struct val
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

struct packet
{
    jobject jpacket;
};

struct record
{
    jobject jrecord;
};

struct rejection_list
{
    int count;
    jobject jrejections;
};
struct rejection
{
    jobject jrejection;
};

struct record_list
{
    int count;
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

#endif