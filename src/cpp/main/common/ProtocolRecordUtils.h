
#ifndef _PROTOCOLRECORDUTILS_H
#define _PROTOCOLRECORDUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"
#include "TypeUtils.h"

/**
 * This is the header for the ProtoclRecordUtils class. 
 * A protocol record contains all containers in a one to one mapping with an 
 * endpoint connection. These containers are collections, classifiers, transformations, and uuids.
 * Procotocl records can be used to retrieve record sets for specified containers.
 * @author Ryan Berkheimer
 */
class ProtocolRecordUtils
{

public:
    /*Default constructor/destructors*/
    ProtocolRecordUtils(JNIEnv *javaEnv, jobject protocolRecord, TypeUtils *typeUtils, ListUtils *listUtils);
    ~ProtocolRecordUtils();

    /*Protocol Record Methods*/
    jobject getProtocolRecords(const char *method, const char *key, const char *val);
    struct record_list *getRecords(const char *method, const char *key = NULL, const char *val = NULL);
    struct record *getRecord(struct record_list *record_list, int index);

private:
    /*Vars*/
    JNIEnv *jvm;
    jobject protocolRecord;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

    /*Protocol Record Methods*/
    jmethodID getRecordsMethodId;
    jmethodID getRecordsByCollectionMethodId;
    jmethodID getRecordsByUUIDMethodId;
    jmethodID getRecordsByTransformationMethodId;
    jmethodID getRecordsByClassifierMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, jobject protocolRecord, TypeUtils *typeUtils, ListUtils *listUtils);

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getMethodSignature(const char *methodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
