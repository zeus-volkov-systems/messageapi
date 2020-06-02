#include <jni.h>
#include <stdio.h>
#include "messageapi_structs.h"
#include "MessageApiTransformationLib.h"
#include "gov_noaa_messageapi_transformations_NativeTransformation.h"

/*
 * Class:     gov_noaa_messageapi_transformations_NativeTransformation
 * Method:    process
 * Signature: (Ljava/lang/Map;)Ljava/lang/List;
 * @author Ryan Berkheimer
 */
JNIEXPORT jobject JNICALL Java_gov_noaa_messageapi_transformations_NativeTransformation_process(JNIEnv *env, jobject transformation, jlong message)
  {
      printf("In our transformation test!\n");
      printf("Hello, World\n");
      fflush(stdout);
      record_list *records = getRecords(message, "test_key");
      printf("Record count: %d\n", records->count);
      fflush(stdout);
      return records->jrecords;
  }

