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

    struct value *getFieldVal(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldVal(field);
    }

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

    struct value *getConditionVal(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionVal(condition);
    }

    int valAsInt(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsInt(value);
    }

    long valAsLong(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsLong(value);
    }

    float valAsFloat(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsFloat(value);
    }

    double valAsDouble(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsDouble(value);
    }

    unsigned char valAsByte(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsByte(value);
    }

    const char *valAsString(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsString(value);
    }

    bool valAsBool(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsBool(value);
    }

    short valAsShort(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsShort(value);
    }

    struct val_list *valAsList(jlong message, struct value *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->valAsList(value);
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

    unsigned char getByteEntry(jlong message, struct val_list *list, int index)
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

    jobject getListEntry(jlong message, struct val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListEntry(list, index);
    }
}