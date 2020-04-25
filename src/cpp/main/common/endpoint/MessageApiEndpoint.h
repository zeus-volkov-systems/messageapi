
#ifndef _Included_MessageApiEndpoint
#define _Included_MessageApiEndpoint

#include <jni.h>
#include <stdbool.h>
#include "endpoint_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

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

    /*Endpoint Methods*/
    struct record *getStateContainer();
    struct field_list *getDefaultFields();
    struct packet *createPacket();
    struct record *createRecord();
    struct rejection *createRejection(struct record* record, const char *reason);

    /*Packet Methods*/
    void addPacketRecord(struct packet *packet, struct record *record);

    /*Protocol Record Methods*/
    jobject getProtocolRecords(const char *method, const char *key, const char *val);
    struct record_list *getRecords(const char *method, const char *key = NULL, const char *val = NULL);
    struct record *getRecord(struct record_list *record_list, int index);

    /*Record Methods*/
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

    /*Field Methods*/
    const char *getFieldId(struct field *field);
    const char *getFieldType(struct field *field);
    struct value *getFieldVal(struct field *field);
    bool getFieldIsValid(struct field *field);
    bool getFieldIsRequired(struct field *field);

    /*Condition Methods*/
    const char *getConditionId(struct condition *condition);
    const char *getConditionType(struct condition *condition);
    const char *getConditionOperator(struct condition *condition);
    struct value *getConditionVal(struct condition *condition);

    /*Value Utility Methods*/
    bool valIsNull(struct value *value);

    /*Value Conversion Methods*/
    int valAsInt(struct value *value);
    long valAsLong(struct value *value);
    float valAsFloat(struct value *value);
    double valAsDouble(struct value *value);
    unsigned char valAsByte(struct value *value);
    const char *valAsString(struct value *value);
    bool valAsBool(struct value *value);
    short valAsShort(struct value *value);
    struct val_list *valAsList(struct value *value);

    /*List Entry Retrieval Methods*/
    jobject getJListEntry(struct val_list *list, int index);
    int getIntEntry(struct val_list *list, int index);
    long getLongEntry(struct val_list *list, int index);
    float getFloatEntry(struct val_list *list, int index);
    double getDoubleEntry(struct val_list *list, int index);
    unsigned char getByteEntry(struct val_list *list, int index);
    const char *getStringEntry(struct val_list *list, int index);
    bool getBoolEntry(struct val_list *list, int index);
    short getShortEntry(struct val_list *list, int index);
    struct val_list *getListEntry(struct val_list *list, int index);

    /*List Creation Method*/
    struct val_list *createList();

    /*List Entry Insertion Methods*/
    void addJListEntry(struct val_list *list, jobject val);
    void addIntEntry(struct val_list *list, int val);
    void addLongEntry(struct val_list *list, long val);
    void addFloatEntry(struct val_list *list, float val);
    void addDoubleEntry(struct val_list *list, double val);
    void addByteEntry(struct val_list *list, unsigned char val);
    void addStringEntry(struct val_list *list, const char* val);
    void addBoolEntry(struct val_list *list, bool val);
    void addShortEntry(struct val_list *list, short val);
    void addListEntry(struct val_list *list, struct val_list *val);

    /*Value Insertion Methods*/
    void setIntVal(void *value_container, int value);

private :
    /*Global References*/
    JNIEnv *jvm;
    jobject endpoint;
    jobject protocolRecord;
    jclass jException;

    jclass jListClass;
    jclass jIntClass;
    jclass jLongClass;
    jclass jFloatClass;
    jclass jDoubleClass;
    jclass jByteClass;
    jclass jStringClass;
    jclass jBoolClass;
    jclass jShortClass;

    /*Endpoint Methods*/
    jmethodID getStateContainerMethodId;
    jmethodID getDefaultFieldsMethodId;
    jmethodID createPacketMethodId;
    jmethodID createRecordMethodId;
    jmethodID createRejectionMethodId;

    /*Packet Methods*/
    jmethodID setPacketRecordsMethodId;
    jmethodID addPacketRecordMethodId;
    jmethodID addPacketRecordsMethodId;
    jmethodID setPacketRejectionsMethodId;
    jmethodID addPacketRejectionMethodId;
    jmethodID addPacketRejectionsMethodId;

    /*Protocol Record Methods*/
    jmethodID getRecordsMethodId;
    jmethodID getRecordsByCollectionMethodId;
    jmethodID getRecordsByUUIDMethodId;
    jmethodID getRecordsByTransformationMethodId;
    jmethodID getRecordsByClassifierMethodId;

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

    /*List Utility Methods*/
    jmethodID createJListMethodId;
    jmethodID getJListSizeMethodId;
    jmethodID addJListItemMethodId;
    jmethodID getJListItemMethodId;

    /*Type Utility Retrieval Methods*/
    jmethodID getJBoolMethodId;
    jmethodID getJByteMethodId;
    jmethodID getJIntMethodId;
    jmethodID getJLongMethodId;
    jmethodID getJFloatMethodId;
    jmethodID getJDoubleMethodId;
    jmethodID getJShortMethodId;

    /*Type Utility Creation Methods*/
    jmethodID createJBoolMethodId;
    jmethodID createJByteMethodId;
    jmethodID createJIntMethodId;
    jmethodID createJLongMethodId;
    jmethodID createJFloatMethodId;
    jmethodID createJDoubleMethodId;
    jmethodID createJShortMethodId;

    /*Load Global Type Class Refs. These can be reused for vals, so the lookup is held and released when returning from native code.*/
    void loadGlobalClassRefs();

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadEndpointMethodIds();
    void loadPacketMethodIds();
    void loadProtocolRecordMethodIds();
    void loadRecordMethodIds();
    void loadFieldMethodIds();
    void loadConditionMethodIds();
    void loadValueTypeMethodIds();

    /*Handles errors allowing throws in java code.*/
    void checkAndThrow(std::string errorMessage);

    /*Lookup for jclass references. Classes returned by these methods should be explicitly released.*/
    jclass getNamedClass(const char *javaClassName);
    jclass getObjectClass(jobject javaObject);

    /*Lookup a java methodID for the given class, method name, and signature string. Also pass in whether method is class static or not.*/
    jmethodID getMethod(jclass javaClass, const char *methodName, const char *methodSignature, bool isStatic);

    /*Utility methods for java list operations*/
    int getJListLength(jobject jList);
    struct string_list *translateFromJavaStringList(jobject jList);

    /*Utility methods for java string operations*/
    jstring toJavaString(const char *charString);
    const char *fromJavaString(jstring javaString);

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getEndpointMethodSignature(const char *endpointMethodName);
    const char *getPacketMethodSignature(const char *packetMethodName);
    const char *getProtocolRecordMethodSignature(const char *protocolRecordMethodName);
    const char *getRecordMethodSignature(const char *recordMethodName);
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
