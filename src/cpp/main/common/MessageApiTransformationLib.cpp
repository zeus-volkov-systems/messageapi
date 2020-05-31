#include <iostream>
#include <string>
#include "MessageApiTransformation.h"
#include "MessageApiTransformationLib.h"
#include "gov_noaa_messageapi_transformations_NativeTransformation.h"

/**
 * Creates a C++ object and returns a pointer to it cast as a long. This allows the NativeEndpoint method
 * to hold onto it and manipulate it during the process method while preventing potential conflicts with
 * other threads or transformations using the same native library. This is used inside the Java process method.
 * The Native process method should be implemented in a separate User class wrapper.
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_transformations_NativeTransformation_create(JNIEnv* env, jobject transformation, jobject transformationMap)
{
    return reinterpret_cast<jlong>(new MessageApiTransformation(env, transformation, transformationMap));
}

/**
 * Deletes the C++ pointer (calls C++ destructor)) that references the object created during transformation construction.
 * This call is made automatically by the Java process method after native processing has completed.
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_transformations_NativeTransformation_release(JNIEnv* env, jobject transformation, jlong transformationLib)
{
    delete reinterpret_cast<MessageApiTransformation *>(transformationLib);
}

extern "C"
{

    struct val_map *getConstructor(jlong message)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getTransformationUtils()->getConstructor();
    }

    struct record_list *getRecords(jlong message, const char *key)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getTransformationUtils()->getRecords(key);
    }

    struct record_list *createRecordList(jlong message)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->createRecordList();
    }

    void addRecord(jlong message, struct record_list *record_list, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->addRecord(record_list, record);
    }

    struct record *getRecord(jlong message, struct record_list *recordList, int recordIndex)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getRecord(recordList, recordIndex);
    }

    struct record *getRecordCopy(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getCopy(record);
    }

    bool getRecordIsValid(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->isValid(record);
    }

    struct string_list *getFieldIds(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getFieldIds(record);
    }

    struct field_list *getFields(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getFields(record);
    }

    struct field *getField(jlong message, struct record *record, const char* fieldId)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getField(record, fieldId);
    }

    bool hasField(jlong message, struct record *record, const char *fieldId)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->hasField(record, fieldId);
    }

    struct string_list *getConditionIds(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getConditionIds(record);
    }

    struct condition_list *getConditions(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getConditions(record);
    }

    struct condition *getCondition(jlong message, struct record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->getCondition(record, conditionId);
    }

    bool hasCondition(jlong message, struct record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRecordUtils()->hasCondition(record, conditionId);
    }

    /*Field Methods*/

    const char *getFieldId(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getId(field);
    }

    const char *getFieldType(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getType(field);
    }

    bool getFieldIsValid(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->isValid(field);
    }

    bool getFieldIsRequired(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->isRequired(field);
    }

    bool getFieldIsNull(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->isNull(field);
    }

    struct val *getFieldVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getVal(field);
    }

    int getFieldIntVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getIntVal(field);
    }

    long getFieldLongVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getLongVal(field);
    }

    float getFieldFloatVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getFloatVal(field);
    }

    double getFieldDoubleVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getDoubleVal(field);
    }

    signed char getFieldByteVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getByteVal(field);
    }

    const char *getFieldStringVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getStringVal(field);
    }

    bool getFieldBoolVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getBoolVal(field);
    }

    short getFieldShortVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getShortVal(field);
    }

    struct val_list *getFieldListVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->getListVal(field);
    }

    void setFieldVal(jlong message, struct field *field, struct val *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setVal(field, value);
    }

    void setFieldIntVal(jlong message, struct field *field, int value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setIntVal(field, value);
    }

    void setFieldLongVal(jlong message, struct field *field, long value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setLongVal(field, value);
    }

    void setFieldFloatVal(jlong message, struct field *field, float value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setFloatVal(field, value);
    }

    void setFieldDoubleVal(jlong message, struct field *field, double value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setDoubleVal(field, value);
    }

    void setFieldByteVal(jlong message, struct field *field, signed char value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setByteVal(field, value);
    }

    void setFieldStringVal(jlong message, struct field *field, const char *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setStringVal(field, value);
    }

    void setFieldBoolVal(jlong message, struct field *field, bool value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setBoolVal(field, value);
    }

    void setFieldShortVal(jlong message, struct field *field, short value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setShortVal(field, value);
    }

    void setFieldListVal(jlong message, struct field *field, struct val_list *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getFieldUtils()->setListVal(field, value);
    }

    /*Condition Methods*/

    const char *getConditionId(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getId(condition);
    }

    const char *getConditionType(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getType(condition);
    }

    const char *getConditionOperator(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getOperator(condition);
    }

    bool getConditionIsNull(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->isNull(condition);
    }

    struct val *getConditionVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getVal(condition);
    }
    
    int getConditionIntVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getIntVal(condition);
    }

    long getConditionLongVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getLongVal(condition);
    }

    float getConditionFloatVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getFloatVal(condition);
    }

    double getConditionDoubleVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getDoubleVal(condition);
    }

    signed char getConditionByteVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getByteVal(condition);
    }

    const char *getConditionStringVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getStringVal(condition);
    }

    bool getConditionBoolVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getBoolVal(condition);
    }

    short getConditionShortVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getShortVal(condition);
    }

    struct val_list *getConditionListVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->getListVal(condition);
    }

    void setConditionVal(jlong message, struct condition *condition, struct val *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setVal(condition, value);
    }

    void setConditionIntVal(jlong message, struct condition *condition, int value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setIntVal(condition, value);
    }

    void setConditionLongVal(jlong message, struct condition *condition, long value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setLongVal(condition, value);
    }

    void setConditionFloatVal(jlong message, struct condition *condition, float value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setFloatVal(condition, value);
    }

    void setConditionDoubleVal(jlong message, struct condition *condition, double value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setDoubleVal(condition, value);
    }

    void setConditionByteVal(jlong message, struct condition *condition, signed char value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setByteVal(condition, value);
    }

    void setConditionStringVal(jlong message, struct condition *condition, const char *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setStringVal(condition, value);
    }

    void setConditionBoolVal(jlong message, struct condition *condition, bool value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setBoolVal(condition, value);
    }

    void setConditionShortVal(jlong message, struct condition *condition, short value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setShortVal(condition, value);
    }

    void setConditionListVal(jlong message, struct condition *condition, struct val_list *value)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getConditionUtils()->setListVal(condition, value);
    }

    /*List Utility Methods*/

    struct list_item *getItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getItem(list, index);
    }

    struct val_list *getListItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getListItem(list, index);
    }

    int getIntItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getIntItem(list, index);
    }

    long getLongItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getLongItem(list, index);
    }

    float getFloatItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getFloatItem(list, index);
    }

    double getDoubleItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getDoubleItem(list, index);
    }

    signed char getByteItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getByteItem(list, index);
    }

    const char *getStringItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getStringItem(list, index);
    }

    bool getBoolItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getBoolItem(list, index);
    }

    short getShortItem(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->getShortItem(list, index);
    }

    struct val_list *createList(jlong message)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->createList();
    }

    void addItem(jlong message, struct val_list *list, struct list_item *item)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addItem(list, item);
    }

    void addIntItem(jlong message, struct val_list *list, int val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addIntItem(list, val);
    }

    void addLongItem(jlong message, struct val_list *list, long val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addLongItem(list, val);
    }

    void addFloatItem(jlong message, struct val_list *list, float val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addFloatItem(list, val);
    }

    void addDoubleItem(jlong message, struct val_list *list, double val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addDoubleItem(list, val);
    }

    void addByteItem(jlong message, struct val_list *list, signed char val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addByteItem(list, val);
    }

    void addStringItem(jlong message, struct val_list *list, const char *val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addStringItem(list, val);
    }

    void addBoolItem(jlong message, struct val_list *list, bool val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addBoolItem(list, val);
    }

    void addShortItem(jlong message, struct val_list *list, short val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addShortItem(list, val);
    }

    void addListItem(jlong message, struct val_list *list, struct val_list *val)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getListUtils()->addListItem(list, val);
    }

    /*Rejection Utils*/
    struct rejection_list *createRejectionList(jlong message)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->createRejectionList();
    }

    void addRejection(jlong message, struct rejection_list *rejection_list, struct rejection *rejection)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->addRejection(rejection_list, rejection);
    }

    struct rejection *getRejectionCopy(jlong message, struct rejection *rejection)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->getCopy(rejection);
    }

    struct record *getRejectionRecord(jlong message, struct rejection *rejection)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->getRecord(rejection);
    }

    struct string_list *getRejectionReasons(jlong message, struct rejection *rejection)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->getReasons(rejection);
    }

    void addRejectionReason(jlong message, struct rejection *rejection, const char *reason)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getRejectionUtils()->addReason(rejection, reason);
    }

    /*Packet Utils*/
    void addPacketRecord(jlong message, struct packet *packet, struct record *record)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->addRecord(packet, record);
    }

    void setPacketRecords(jlong message, struct packet *packet, struct record_list *records)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->setRecords(packet, records);
    }

    void addPacketRecords(jlong message, struct packet *packet, struct record_list *records)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->addRecords(packet, records);
    }

    void setPacketRejections(jlong message, struct packet *packet, struct rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->setRejections(packet, rejections);
    }

    void addPacketRejection(jlong message, struct packet *packet, struct rejection *rejection)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->addRejection(packet, rejection);
    }

    void addPacketRejections(jlong message, struct packet *packet, struct rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->addRejections(packet, rejections);
    }

    struct record_list *getPacketRecords(jlong message, struct packet *packet)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->getRecords(packet);
    }

    struct rejection_list *getPacketRejections(jlong message, struct packet *packet)
    {
        return reinterpret_cast<MessageApiTransformation *>(message)->getPacketUtils()->getRejections(packet);
    }
}