
#ifndef _Included_MessageApiEndpoint
#define _Included_MessageApiEndpoint

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"
#include "EndpointUtils.h"
#include "ProtocolRecordUtils.h"
#include "RecordUtils.h"
#include "RejectionUtils.h"
#include "FieldUtils.h"
#include "ConditionUtils.h"
#include "PacketUtils.h"

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
    /*Default constructor/destructors*/
    MessageApiEndpoint(JNIEnv* javaEnv, jobject jEndpoint, jobject jProtocolRecord);
    ~MessageApiEndpoint();

    /*Utils Accessors*/
    EndpointUtils *getEndpointUtils();
    ProtocolRecordUtils *getProtocolRecordUtils();
    RecordUtils *getRecordUtils();
    RejectionUtils *getRejectionUtils();
    FieldUtils *getFieldUtils();
    ConditionUtils *getConditionUtils();
    PacketUtils *getPacketUtils();
    ListUtils *getListUtils();
    TypeUtils *getTypeUtils();

private :
    /*Global References*/
    JNIEnv *jvm;
    jobject endpoint;
    jobject protocolRecord;
    
    EndpointUtils *endpointUtils;
    ProtocolRecordUtils *protocolRecordUtils;
    RecordUtils *recordUtils;
    RejectionUtils *rejectionUtils;
    FieldUtils *fieldUtils;
    ConditionUtils *conditionUtils;
    PacketUtils *packetUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
