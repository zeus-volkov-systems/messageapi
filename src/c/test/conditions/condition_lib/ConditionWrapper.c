#include <jni.h>
#include <stdio.h>
#include "messageapi_structs.h"
#include "MessageApiConditionLib.h"
#include "gov_noaa_messageapi_conditions_NativeCondition.h"

/*
 * Class:     gov_noaa_messageapi_conditions_NativeCondition
 * Method:    compare
 * Signature: (J)Z
 * @author Ryan Berkheimer
 */
JNIEXPORT bool JNICALL Java_gov_noaa_messageapi_conditions_NativeCondition_compare(JNIEnv *env, jobject nativeCondition, jlong message)
  {
      printf("In our native condition comparison test!\n");
      fflush(stdout);
      condition *condition = getCondition(message);
      field *field = getField(message);
      int fieldVal = getFieldIntVal(message, field);
      int condVal = getConditionIntVal(message, condition);
      if (fieldVal >= condVal) {
          printf("The field val was greater than or equal to the cond val, passed condition test!\n");
          fflush(stdout);
          return true;
      } else {
          printf("The field val was less than the condition val, failed the condition test!\n");
          fflush(stdout);
          return false;
      }
      
  }

