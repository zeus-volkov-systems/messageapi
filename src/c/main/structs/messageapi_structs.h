
#ifndef _Included_messageapi_structs
#define _Included_messageapi_structs

#include <jni.h>

/**
 * @author Ryan Berkheimer
 */

typedef struct map_val
{
    jobject jval;
} map_val;

typedef struct val_map
{
    jobject jmap;
} val_map;

typedef struct list_item
{
    jobject jitem;
} list_item;

typedef struct val_list
{
    int count;
    jobject jlist;
} val_list;

typedef struct session
{
    jlong sessionLib;
} session;

typedef struct transformation
{
    jobject jtransformation;
} transformation;

typedef struct transformation_map
{
    jobject jtransformation_map;
} transformation_map;

typedef struct response
{
    jobject jresponse;
} response;

typedef struct request
{
    jobject jrequest;
} request;

typedef struct condition
{
    jobject jcondition;
} condition;

typedef struct condition_list
{
    int count;
    struct condition **conditions;
} condition_list;
typedef struct val
{
    jobject jvalue;
} val;

typedef struct field
{
    jobject jfield;
} field;

typedef struct field_list
{
    int count;
    struct field **fields;
} field_list;

typedef struct packet
{
    jobject jpacket;
} packet;

typedef struct record
{
    jobject jrecord;
} record;

typedef struct rejection_list
{
    int count;
    jobject jrejections;
} rejection_list;

typedef struct rejection
{
    jobject jrejection;
} rejection;

typedef struct record_list
{
    int count;
    jobject jrecords;
} record_list;


typedef struct string_list
{
    int count;
    int max_length;
    char **strings;
} string_list;

typedef struct classifier
{
    char* key;
    char* val;
} classifier;

#endif