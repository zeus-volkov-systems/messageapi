
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
    PacketUtils *getPacketUtils();
    ListUtils *getListUtils();
    TypeUtils *getTypeUtils();

    /*Condition Methods*/
    const char *getConditionId(struct condition *condition);
    const char *getConditionType(struct condition *condition);
    const char *getConditionOperator(struct condition *condition);
    bool getConditionIsNull(struct condition *condition);
    struct val *getConditionVal(struct condition *condition);
    int getConditionIntVal(struct condition *condition);
    long getConditionLongVal(struct condition *condition);
    float getConditionFloatVal(struct condition *condition);
    double getConditionDoubleVal(struct condition *condition);
    signed char getConditionByteVal(struct condition *condition);
    const char *getConditionStringVal(struct condition *condition);
    bool getConditionBoolVal(struct condition *condition);
    short getConditionShortVal(struct condition *condition);
    struct val_list *getConditionListVal(struct condition *condition);
    void setConditionVal(struct condition *condition, struct val *value);
    void setConditionIntVal(struct condition *condition, int value);
    void setConditionLongVal(struct condition *condition, long value);
    void setConditionFloatVal(struct condition *condition, float value);
    void setConditionDoubleVal(struct condition *condition, double value);
    void setConditionByteVal(struct condition *condition, signed char value);
    void setConditionStringVal(struct condition *condition, const char *value);
    void setConditionBoolVal(struct condition *condition, bool value);
    void setConditionShortVal(struct condition *condition, short value);
    void setConditionListVal(struct condition *condition, struct val_list *value);

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
    PacketUtils *packetUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

    /*Condition Methods*/
    jmethodID getConditionIdMethodId;
    jmethodID getConditionTypeMethodId;
    jmethodID getConditionOperatorMethodId;
    jmethodID getConditionValueMethodId;
    jmethodID setConditionValueMethodId;


    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadConditionMethodIds();

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getConditionMethodSignature(const char *conditionMethodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
