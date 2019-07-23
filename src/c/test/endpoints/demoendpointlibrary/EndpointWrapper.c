#include <jni.h>
#include <stdio.h>
#include "MessageApiEndpointLib.h"
#include "gov_noaa_messageapi_endpoints_NativeEndpoint.h"

/*
 * Class:     gov_noaa_messageapi_endpoints_NativeEndpoint
 * Method:    process
 * Signature: (Lgov/noaa/messageapi/interfaces/IProtocolRecord;)Lgov/noaa/messageapi/interfaces/IPacket;
 * @author Ryan Berkheimer
 */
JNIEXPORT jobject JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_process(JNIEnv *env, jobject endpoint, jlong message)
  {
      printf("In our test!\n");
      printf("Hello, World\n");
      fflush(stdout);
      //struct records_vector records_vector = messageapi_endpoint_getrecordsvector(message);
      //printf(records_vector.count);
      //printf(records_vector.records[0]);
      //printf("Leaving our test!");
      return;
  }

