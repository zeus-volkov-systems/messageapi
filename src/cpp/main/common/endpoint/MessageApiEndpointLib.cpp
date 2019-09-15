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
    struct records_vector *messageapi_endpoint_getrecordsvector(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecords("getRecords");
    }

    /*const char *taskapi_getproperty(jlong libptr, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(libptr)->getProperty(key);
    }

    jobject taskapi_getobject(jlong libptr, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(libptr)->getObject(key);
    }

    void taskapi_addobject(jlong libptr, const char *key, jobject value)
    {
        reinterpret_cast<MessageApiEndpoint *>(libptr)->addObject(key, value);
    }*/


}