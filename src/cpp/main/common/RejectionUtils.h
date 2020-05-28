
#ifndef _REJECTIONUTILS_H
#define _REJECTIONUTILS_H

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
 * This is the header for the RejectionUtils class. 
 * A record contains fields and conditions.
 */
class RejectionUtils
{

public:
    /*Default constructor/destructors*/
    RejectionUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils);
    ~RejectionUtils();

    /*Rejection Methods*/
    struct rejection_list *createRejectionList();
    void addRejection(struct rejection_list *rejection_list, struct rejection *rejection);
    struct rejection *getCopy(struct rejection *rejection);
    struct record *getRecord(struct rejection *rejection);
    struct string_list *getReasons(struct rejection *rejection);
    void addReason(struct rejection *rejection, const char *reason);

private:
    /*Vars*/
    JNIEnv *jvm;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

    /*Rejection Methods*/
    jmethodID getCopyMethodId;
    jmethodID getReasonsMethodId;
    jmethodID getRecordMethodId;
    jmethodID addReasonMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils, ListUtils *listUtils);

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
