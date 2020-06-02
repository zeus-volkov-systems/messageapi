#ifndef _Included_MessageApiSession
#define _Included_MessageApiSession

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "MapUtils.h"
#include "ListUtils.h"
#include "SessionUtils.h"
#include "RequestUtils.h"
#include "ResponseUtils.h"
#include "RecordUtils.h"
#include "RejectionUtils.h"
#include "FieldUtils.h"
#include "ConditionUtils.h"
#include "PacketUtils.h"

/**
 * @author Ryan Berkheimer
 */
class MessageApiSession
{

public:
    /*Default constructor*/
    MessageApiSession(JNIEnv *javaEnv, jobject jSession);
    /*Default destructor*/
    ~MessageApiSession();

    /*Utils Accessors*/
    SessionUtils *getSessionUtils();
    RequestUtils *getRequestUtils();
    ResponseUtils *getResponseUtils();
    RecordUtils *getRecordUtils();
    RejectionUtils *getRejectionUtils();
    FieldUtils *getFieldUtils();
    ConditionUtils *getConditionUtils();
    PacketUtils *getPacketUtils();
    ListUtils *getListUtils();
    MapUtils *getMapUtils();
    TypeUtils *getTypeUtils();

private :
    /*Global References*/
    JNIEnv *jvm;
    jobject session;
    
    SessionUtils *sessionUtils;
    RequestUtils *requestUtils;
    ResponseUtils *responseUtils;
    RecordUtils *recordUtils;
    RejectionUtils *rejectionUtils;
    FieldUtils *fieldUtils;
    ConditionUtils *conditionUtils;
    PacketUtils *packetUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;
    MapUtils *mapUtils;

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
