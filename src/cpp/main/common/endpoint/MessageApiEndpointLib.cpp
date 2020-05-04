#include <iostream>
#include <string>
#include <jni.h>
#include "MessageApiEndpoint.h"
#include "MessageApiEndpointLib.h"
#include "gov_noaa_messageapi_endpoints_NativeEndpoint.h"

/**
 * Creates a C++ object and returns a pointer to it cast as a long. This allows the NativeEndpoint method
 * to hold onto it and manipulate it during the process method while preventing potential conflicts with
 * other threads or endpoints using the same native library. This is used inside the Java process method.
 * The Native process method should be implemented in a separate User class wrapper.
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_create(JNIEnv* env, jobject endpoint, jobject record)
{
    return reinterpret_cast<jlong>(new MessageApiEndpoint(env, endpoint, record));
}

/**
 * Deletes the C++ pointer (calls C++ destructor)) that references the object created during endpoint construction.
 * This call is made automatically by the Java process method after native processing has completed.
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_release(JNIEnv* env, jobject task, jlong messageapilib)
{
    delete reinterpret_cast<MessageApiEndpoint *>(messageapilib);
}

extern "C"
{

    struct record *getStateContainer(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getStateContainer();
    }

    struct field_list *getDefaultFields(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getDefaultFields();
    }

    struct packet *createPacket(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->createPacket();
    }

    struct record *createRecord(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->createRecord();
    }

    struct rejection *createRejection(jlong message, struct record *record, const char *reason)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->createRejection(record, reason);
    }

    struct record_list *getRecords(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecords");
    }

    struct record_list *getRecordsByCollection(jlong message, const char *collectionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByCollection", collectionId);
    }

    struct record_list *getRecordsByTransformation(jlong message, const char *transformationId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByTransformation", transformationId);
    }

    struct record_list *getRecordsByUUID(jlong message, const char *uuid)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByUUID", uuid);
    }

    struct record_list *getRecordsByClassifier(jlong message, const char *classifierKey, const char *classifierValue)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByClassifier", classifierKey, classifierValue);
    }

    struct record *getRecord(jlong message, struct record_list *recordList, int recordIndex)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecord(recordList, recordIndex);
    }

    struct record *getRecordCopy(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordCopy(record);
    }

    bool getRecordIsValid(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordIsValid(record);
    }

    struct string_list *getFieldIds(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIds(record);
    }

    struct field_list *getFields(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFields(record);
    }

    struct field *getField(jlong message, struct record *record, const char* fieldId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getField(record, fieldId);
    }

    bool hasField(jlong message, struct record *record, const char *fieldId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordHasField(record, fieldId);
    }

    struct string_list *getConditionIds(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionIds(record);
    }

    struct condition_list *getConditions(jlong message, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditions(record);
    }

    struct condition *getCondition(jlong message, struct record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getCondition(record, conditionId);
    }

    bool hasCondition(jlong message, struct record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordHasCondition(record, conditionId);
    }

    /*Field Methods*/

    const char *getFieldId(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldId(field);
    }

    const char *getFieldType(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldType(field);
    }

    bool getFieldIsValid(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIsValid(field);
    }

    bool getFieldIsRequired(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIsRequired(field);
    }

    bool getFieldIsNull(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIsNull(field);
    }

    struct val *getFieldVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldVal(field);
    }

    int getFieldIntVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIntVal(field);
    }

    long getFieldLongVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldLongVal(field);
    }

    float getFieldFloatVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldFloatVal(field);
    }

    double getFieldDoubleVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldDoubleVal(field);
    }

    signed char getFieldByteVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldByteVal(field);
    }

    const char *getFieldStringVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldStringVal(field);
    }

    bool getFieldBoolVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldBoolVal(field);
    }

    short getFieldShortVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldShortVal(field);
    }

    struct val_list *getFieldListVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldListVal(field);
    }

    void setFieldVal(jlong message, struct field *field, struct val *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldVal(field, value);
    }

    void setFieldIntVal(jlong message, struct field *field, int value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldIntVal(field, value);
    }

    void setFieldLongVal(jlong message, struct field *field, long value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldLongVal(field, value);
    }

    void setFieldFloatVal(jlong message, struct field *field, float value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldFloatVal(field, value);
    }

    void setFieldDoubleVal(jlong message, struct field *field, double value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldDoubleVal(field, value);
    }

    void setFieldByteVal(jlong message, struct field *field, signed char value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldByteVal(field, value);
    }

    void setFieldStringVal(jlong message, struct field *field, const char *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldStringVal(field, value);
    }

    void setFieldBoolVal(jlong message, struct field *field, bool value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldBoolVal(field, value);
    }

    void setFieldShortVal(jlong message, struct field *field, short value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldShortVal(field, value);
    }

    void setFieldListVal(jlong message, struct field *field, struct val_list *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setFieldListVal(field, value);
    }

    /*Condition Methods*/

    const char *getConditionId(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionId(condition);
    }

    const char *getConditionType(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionType(condition);
    }

    const char *getConditionOperator(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionOperator(condition);
    }

    bool getConditionIsNull(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionIsNull(condition);
    }

    struct val *getConditionVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionVal(condition);
    }
    
    int getConditionIntVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionIntVal(condition);
    }

    long getConditionLongVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionLongVal(condition);
    }

    float getConditionFloatVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionFloatVal(condition);
    }

    double getConditionDoubleVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionDoubleVal(condition);
    }

    signed char getConditionByteVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionByteVal(condition);
    }

    const char *getConditionStringVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionStringVal(condition);
    }

    bool getConditionBoolVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionBoolVal(condition);
    }

    short getConditionShortVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionShortVal(condition);
    }

    struct val_list *getConditionListVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionListVal(condition);
    }

    void setConditionVal(jlong message, struct condition *condition, struct val *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionVal(condition, value);
    }

    void setConditionIntVal(jlong message, struct condition *condition, int value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionIntVal(condition, value);
    }

    void setConditionLongVal(jlong message, struct condition *condition, long value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionLongVal(condition, value);
    }

    void setConditionFloatVal(jlong message, struct condition *condition, float value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionFloatVal(condition, value);
    }

    void setConditionDoubleVal(jlong message, struct condition *condition, double value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionDoubleVal(condition, value);
    }

    void setConditionByteVal(jlong message, struct condition *condition, signed char value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionByteVal(condition, value);
    }

    void setConditionStringVal(jlong message, struct condition *condition, const char *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionStringVal(condition, value);
    }

    void setConditionBoolVal(jlong message, struct condition *condition, bool value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionBoolVal(condition, value);
    }

    void setConditionShortVal(jlong message, struct condition *condition, short value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionShortVal(condition, value);
    }

    void setConditionListVal(jlong message, struct condition *condition, struct val_list *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->setConditionListVal(condition, value);
    }

    /*List Utility Methods*/

    struct list_entry *getEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEntry(list, index);
    }

    struct val_list *getListEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListEntry(list, index);
    }

    int getIntEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getIntEntry(list, index);
    }

    long getLongEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getLongEntry(list, index);
    }

    float getFloatEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFloatEntry(list, index);
    }

    double getDoubleEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getDoubleEntry(list, index);
    }

    signed char getByteEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getByteEntry(list, index);
    }

    const char *getStringEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getStringEntry(list, index);
    }

    bool getBoolEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getBoolEntry(list, index);
    }

    short getShortEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getShortEntry(list, index);
    }

    struct val_list *createList(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->createList();
    }

    void addEntry(jlong message, struct val_list *list, struct list_entry *entry)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addEntry(list, entry);
    }

    void addIntEntry(jlong message, struct val_list *list, int val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addIntEntry(list, val);
    }

    void addLongEntry(jlong message, struct val_list *list, long val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addLongEntry(list, val);
    }

    void addFloatEntry(jlong message, struct val_list *list, float val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addFloatEntry(list, val);
    }

    void addDoubleEntry(jlong message, struct val_list *list, double val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addDoubleEntry(list, val);
    }

    void addByteEntry(jlong message, struct val_list *list, signed char val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addByteEntry(list, val);
    }

    void addStringEntry(jlong message, struct val_list *list, const char *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addStringEntry(list, val);
    }

    void addBoolEntry(jlong message, struct val_list *list, bool val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addBoolEntry(list, val);
    }

    void addShortEntry(jlong message, struct val_list *list, short val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addShortEntry(list, val);
    }

    void addListEntry(jlong message, struct val_list *list, struct val_list *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addListEntry(list, val);
    }

    /*Packet Utils*/
    void addPacketRecord(jlong message, struct packet *packet, struct record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->addPacketRecord(packet, record);
    }
}