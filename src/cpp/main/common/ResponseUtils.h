
#ifndef _RESPONSEUTILS_H
#define _RESPONSEUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>
#include "ListUtils.h"
#include "TypeUtils.h"

/**
 * Responses are returned by calling submit on a request. Responses operate asynchronously,
 * setting an isComplete flag from false to true whenever the specified process is complete.
 * Responses execute the request, and holds records and/or rejections
 * that are returned by the evaluation of the request. These records are an aggregate of all
 * computation paths through a given request, so may contain records gathered from multiple sources
 * in the same computation.
 * 
 * @author Ryan Berkheimer
 */
class ResponseUtils
{

public:
    /*Default constructor/destructors*/
    ResponseUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils);
    ~ResponseUtils();

    /* Response Methods */
    bool isComplete(struct response *response);
    struct request *getRequest(struct response *response);
    struct rejection_list *getRejections(struct response *response);
    struct record_list *getRecords(struct response *response);
    void setRejections(struct response *response, struct rejection_list *rejections);
    void setRecords(struct response *response, struct record_list *records);
    void setComplete(struct response *response, bool isComplete);

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;
    TypeUtils *typeUtils;

    /*Request Methods*/
    jmethodID isCompleteMethodId;
    jmethodID getRequestMethodId;
    jmethodID getRejectionsMethodId;
    jmethodID getRecordsMethodId;
    jmethodID setRejectionsMethodId;
    jmethodID setRecordsMethodId;
    jmethodID setCompleteMethodId;


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
