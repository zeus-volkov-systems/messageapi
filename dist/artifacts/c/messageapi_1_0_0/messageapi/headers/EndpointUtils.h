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
#include "TypeUtils.h"

/**
 * This is the header for the EndpointUtils class. 
 * An endpoint, or endpoint connection, is a terminus for a given process. Endpoint connections
 * consume records, evaluate containers, send and/or retrieve data, and create and return
 * packets containing a return record/rejection set. This set of utils contains all API methods
 * exposed to the user that can manipulate system properties directly managed by endpoints.
 * Native endpoint connections also have access to a special construct called a state container.
 * This state container is a regular record that is persistent through multiple endpoint connection
 * calls.
 *  
 * @author Ryan Berkheimer
 */
class EndpointUtils
{

public:
    /*Default constructor/destructors*/
    EndpointUtils(JNIEnv *javaEnv, jobject endpoint, TypeUtils *typeUtils, ListUtils *listUtils);
    ~EndpointUtils();

    /*Endpoint Methods*/
    struct record *getStateContainer();
    struct field_list *getDefaultFields();
    struct val_map *getConstructor();
    struct packet *createPacket();
    struct record *createRecord();
    struct rejection *createRejection(struct record *record, const char *reason);

private:
    /*Vars*/
    JNIEnv *jvm;
    jobject endpoint;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

    /*Endpoint Methods*/
    jmethodID getStateContainerMethodId;
    jmethodID getDefaultFieldsMethodId;
    jmethodID getConstructorMethodId;
    jmethodID createPacketMethodId;
    jmethodID createRecordMethodId;
    jmethodID createRejectionMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, jobject endpoint, TypeUtils *typeUtils, ListUtils *listUtils);

    const char *getMethodSignature(const char *methodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
