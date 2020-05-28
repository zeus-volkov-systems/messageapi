
#ifndef _ENDPOINTUTILS_H
#define _ENDPOINTUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"

/**
 * This is the header for the EndpointUtils class. 
 * An endpoint, or endpoint connection, is a terminus for a given process. Endpoint connections
 * consume records, evaluate containers, send and/or retrieve data, and create and return
 * packets containing a return record/rejection set. This set of utils contains all API methods
 * exposed to the user that can manipulate system properties directly managed by endpoints.
 *  
 * @author Ryan Berkheimer
 */
class EndpointUtils
{

public:
    /*Default constructor/destructors*/
    EndpointUtils(JNIEnv *javaEnv, ListUtils *listUtils);
    ~EndpointUtils();

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, ListUtils *listUtils);

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
