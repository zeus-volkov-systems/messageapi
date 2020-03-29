
#ifndef _Included_MessageApiEndpoint
#define _Included_MessageApiEndpoint

#include <jni.h>
#include <stdbool.h>
#include "endpoint_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

/**
 * This is the header for the MessageApiEndpoint class - this class is the native side facility
 * for doing endpoint processing and communicating back with the java side. This class holds
 * three private vars - a pointer to the jvm where the call originated from, a pointer to the
 * endpoint class instance (jobject), and a pointer to the protocol record that holds data for
 * this endpoint to process (jobject). To the user of the MessageApiEndpoint library in the native side,
 * they will see the entire library as a single jlong. This jlong holds a pointer to this class,
 * making it easier for implementors to ignore most of the details of implementation.
 * @author Ryan Berkheimer
 */
class MessageApiEndpoint
{

public:
    MessageApiEndpoint(JNIEnv* javaEnv, jobject jEndpoint, jobject jProtocolRecord);
    ~MessageApiEndpoint();

    jobject getProtocolRecords(jobject protocolref, jmethodID methodId, const char* method, const char* key, const char* val);
    
    struct record_list *getRecords(const char *method, const char *key = NULL, const char *val = NULL);
    struct string_list *getFieldNames(struct record *record);
    struct field_list *getFields(struct record *record);
    struct field *getField(struct record *record, const char* fieldName);

private:
    JNIEnv* jvm;
    jobject endpoint;
    jobject protocolRecord;

    jclass java_util_List;
    jmethodID java_util_List_size;
    jmethodID java_util_List_get;

    void checkAndThrow(const char *errorMessage);

    JNIEnv *getJVM();
    jclass getNamedClass(const char *javaClassName);
    jclass getObjectClass(jobject javaObject);
    jmethodID getMethod(jclass javaClass, const char *methodName, const char *methodSignature, bool isStatic);
    jstring toJavaString(const char *charString);
    const char *fromJavaString(jstring javaString);
    const char *getRecordMethodSignature(const char *recordMethodName);
    const char *getFieldMethodSignature(const char *fieldMethodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
