/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class gov_noaa_messageapi_endpoints_NativeEndpoint */

#ifndef _Included_gov_noaa_messageapi_endpoints_NativeEndpoint
#define _Included_gov_noaa_messageapi_endpoints_NativeEndpoint
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     gov_noaa_messageapi_endpoints_NativeEndpoint
 * Method:    process
 * Signature: (J)Lgov/noaa/messageapi/interfaces/IPacket;
 */
JNIEXPORT jobject JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_process
  (JNIEnv *, jobject, jlong);

/*
 * Class:     gov_noaa_messageapi_endpoints_NativeEndpoint
 * Method:    create
 * Signature: (Lgov/noaa/messageapi/interfaces/IProtocolRecord;)J
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_create
  (JNIEnv *, jobject, jobject);

/*
 * Class:     gov_noaa_messageapi_endpoints_NativeEndpoint
 * Method:    release
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_release
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif