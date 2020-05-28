
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
    PacketUtils *getPacketUtils();
    ListUtils *getListUtils();
    TypeUtils *getTypeUtils();


    /*Record Methods*/
    struct record_list *createRecordList();
    void addRecord(struct record_list *record_list, struct record *record);
    struct record *getRecordCopy(struct record *record);
    bool getRecordIsValid(struct record *record);

    bool getRecordHasField(struct record *record, const char *fieldId);
    struct string_list *getFieldIds(struct record *record);
    struct field_list *getFields(struct record *record);
    struct field *getField(struct record *record, const char* fieldId);

    bool getRecordHasCondition(struct record *record, const char *conditionId);
    struct string_list *getConditionIds(struct record *record);
    struct condition_list *getConditions(struct record *record);
    struct condition *getCondition(struct record *record, const char *conditionId);

    /*Rejection Methods*/
    struct rejection_list *createRejectionList();
    void addRejection(struct rejection_list *rejection_list, struct rejection *rejection);
    struct rejection *getRejectionCopy(struct rejection *rejection);
    struct record *getRejectionRecord(struct rejection *rejection);
    struct string_list *getRejectionReasons(struct rejection *rejection);
    void addRejectionReason(struct rejection *rejection, const char *reason);

    /*Field Methods*/
    const char *getFieldId(struct field *field);
    const char *getFieldType(struct field *field);
    bool getFieldIsValid(struct field *field);
    bool getFieldIsRequired(struct field *field);
    bool getFieldIsNull(struct field *field);
    struct val *getFieldVal(struct field *field);
    int getFieldIntVal(struct field *field);
    long getFieldLongVal(struct field *field);
    float getFieldFloatVal(struct field *field);
    double getFieldDoubleVal(struct field *field);
    signed char getFieldByteVal(struct field *field);
    const char *getFieldStringVal(struct field *field);
    bool getFieldBoolVal(struct field *field);
    short getFieldShortVal(struct field *field);
    struct val_list *getFieldListVal(struct field *field);
    void setFieldVal(struct field *field, struct val *value);
    void setFieldIntVal(struct field *field, int value);
    void setFieldLongVal(struct field *field, long value);
    void setFieldFloatVal(struct field *field, float value);
    void setFieldDoubleVal(struct field *field, double value);
    void setFieldByteVal(struct field *field, signed char value);
    void setFieldStringVal(struct field *field, const char *value);
    void setFieldBoolVal(struct field *field, bool value);
    void setFieldShortVal(struct field *field, short value);
    void setFieldListVal(struct field *field, struct val_list *value);

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
    PacketUtils *packetUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;

    /*Record Methods*/
    jmethodID getRecordIsValidMethodId;
    jmethodID getRecordCopyMethodId;
    jmethodID getRecordFieldIdsMethodId;
    jmethodID getRecordFieldsMethodId;
    jmethodID getRecordFieldMethodId;
    jmethodID getRecordHasFieldMethodId;
    jmethodID getRecordConditionIdsMethodId;
    jmethodID getRecordConditionsMethodId;
    jmethodID getRecordHasConditionMethodId;
    jmethodID getRecordConditionMethodId;

    /*Rejection Methods*/
    jmethodID getRejectionCopyMethodId;
    jmethodID getRejectionReasonsMethodId;
    jmethodID getRejectionRecordMethodId;
    jmethodID addRejectionReasonMethodId;

    /*Field Methods*/
    jmethodID getFieldIdMethodId;
    jmethodID getFieldTypeMethodId;
    jmethodID getFieldValueMethodId;
    jmethodID getFieldIsValidMethodId;
    jmethodID getFieldIsRequiredMethodId;
    jmethodID setFieldValueMethodId;

    /*Condition Methods*/
    jmethodID getConditionIdMethodId;
    jmethodID getConditionTypeMethodId;
    jmethodID getConditionOperatorMethodId;
    jmethodID getConditionValueMethodId;
    jmethodID setConditionValueMethodId;


    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadRecordMethodIds();
    void loadRejectionMethodIds();
    void loadFieldMethodIds();
    void loadConditionMethodIds();

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getRecordMethodSignature(const char *recordMethodName);
    const char *getRejectionMethodSignature(const char *rejectionMethodName);
    const char *getFieldMethodSignature(const char *fieldMethodName);
    const char *getConditionMethodSignature(const char *conditionMethodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
