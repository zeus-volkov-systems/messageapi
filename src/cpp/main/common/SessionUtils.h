#ifndef _SESSIONUTILS_H
#define _SESSIONUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"

/**
 * Sessions are the top level API container of any given computation. Sessions
 * bootstrap from a specification map and 'lock-in' a computation environment,
 * allowing requests to be created.
 * 
 * @author Ryan Berkheimer
 */
class SessionUtils
{

public:
    /*Default constructor */
    SessionUtils(JNIEnv *javaEnv, jobject jSession);

    /*Default Destructor */
    ~SessionUtils();

    /* Session Methods */
    struct request *createRequest();

private:
    /*Vars*/
    JNIEnv *jvm;
    jobject session;

    /*Request Methods*/
    jmethodID createRequestMethodId;


    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, jobject session);

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
