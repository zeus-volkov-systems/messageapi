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
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_create(JNIEnv *env, jobject endpoint, jobject record)
{
    return reinterpret_cast<jlong>(new MessageApiEndpoint(env, endpoint, record));
}

/**
 * Deletes the C++ pointer (calls C++ destructor)) that references the object created during endpoint construction.
 * This call is made automatically by the Java process method after native processing has completed.
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_release(JNIEnv *, jobject task, jlong messageapilib)
{
    delete reinterpret_cast<MessageApiEndpoint *>(messageapilib);
}

extern "C"
{
    struct records_vector* getRecords(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecords");
    }

    struct records_vector* getRecordsByCollection(jlong message, const char* collectionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByCollection", collectionId);
    }

    struct records_vector* getRecordsByTransformation(jlong message, const char* transformationId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByTransformation", transformationId);
    }

    struct records_vector *getRecordsByUUID(jlong message, const char *uuid)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByTransformation", uuid);
    }

    struct records_vector* getRecordsByClassifier(jlong message, const char* classifierKey, const char* classifierValue)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecordsByClassifier", classifierKey, classifierValue);
    }

    /*
    void taskapi_addobject(jlong libptr, const char *key, jobject value)
    {
        reinterpret_cast<MessageApiEndpoint *>(libptr)->addObject(key, value);
    }*/


}