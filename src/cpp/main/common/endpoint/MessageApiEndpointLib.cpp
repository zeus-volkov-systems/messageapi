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

    struct field_value *getFieldValue(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldValue(field);
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

    struct condition_value *getConditionValue(jlong message, struct condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionValue(condition);
    }

    int fieldValueAsInteger(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsInteger(field_value);
    }

    long fieldValueAsLong(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsLong(field_value);
    }

    float fieldValueAsFloat(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsFloat(field_value);
    }

    double fieldValueAsDouble(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsDouble(field_value);
    }

    unsigned char fieldValueAsByte(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsByte(field_value);
    }

    const char *fieldValueAsString(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsString(field_value);
    }

    bool fieldValueAsBoolean(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsBoolean(field_value);
    }

    short fieldValueAsShort(jlong message, struct field_value *field_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->fieldValueAsShort(field_value);
    }

    int conditionValueAsInteger(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsInteger(condition_value);
    }

    long conditionValueAsLong(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsLong(condition_value);
    }

    float conditionValueAsFloat(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsFloat(condition_value);
    }

    double conditionValueAsDouble(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsDouble(condition_value);
    }

    unsigned char conditionValueAsByte(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsByte(condition_value);
    }

    const char *conditionValueAsString(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsString(condition_value);
    }

    bool conditionValueAsBoolean(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsBoolean(condition_value);
    }

    short conditionValueAsShort(jlong message, struct condition_value *condition_value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->conditionValueAsShort(condition_value);
    }
}