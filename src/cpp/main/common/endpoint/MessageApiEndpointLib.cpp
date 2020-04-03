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

    const char *getFieldId(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldId(field);
    }

    const char *getFieldType(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldType(field);
    }

    void *getFieldValue(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldValue(field);
    }

    bool getFieldIsValid(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIsValid(field);
    }

    bool getFieldIsRequired(jlong message, struct field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldIsRequired(field);
    }
}