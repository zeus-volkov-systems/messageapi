#include <iostream>
#include <string>
#include <jni.h>
#include "messageapi_native_lib.h"
#include "messageapi_functions.h"
#include "gov_noaa_messageapi_endpoints_BaseNativeEndpoint.h"

/**
 * @author Ryan Berkheimer
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_taskapi_tasks_NativeTask_newNativeLibInstance(JNIEnv *env, jobject endpoint, jobject record)
{
    return reinterpret_cast<jlong>(new MessageApiNativeLib(env, endpoint, record));
}

JNIEXPORT void JNICALL Java_gov_noaa_taskapi_tasks_NativeTask_releaseNativeLibInstance(JNIEnv *, jobject task, jlong tasklibptr)
{
    delete reinterpret_cast<MessageApiNativeLib *>(tasklibptr);
}

extern "C"
{

}
