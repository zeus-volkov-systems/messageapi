
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
    MessageApiEndpoint(JNIEnv *, jobject, jobject);
    ~MessageApiEndpoint();

    void checkAndThrow(const char *);

    JNIEnv *getJVM();
    jclass getNamedClass(const char *);
    jclass getObjectClass(jobject);
    jmethodID getMethod(jclass, const char *, const char *, bool);
    jstring toJavaString(const char *);
    const char *fromJavaString(jstring);
    const char* getRecordMethodSignature(const char *);
    jobject getProtocolRecords(jobject protocolref, jmethodID methodId, const char *method, const char *key, const char *val);
    
    struct records_vector *getRecords(const char *method, const char *key = NULL, const char *val = NULL);
    struct string_vector *getTransformations();

private:
    JNIEnv *jvm;
    jobject endpoint;
    jobject protocolRecord;
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
