#include <jni.h>
#include <stdio.h>
#include "endpoint_structs.h"
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
      struct record_list* default_record_list = getRecords(message);
      //struct record_list* classifier_record_list = getRecordsByClassifier(message, "color", "blue");
      //struct record_list* collection_record_list = getRecordsByCollection(message, "gold");
      //struct record_list* transformation_record_list = getRecordsByTransformation(message, "combine-colors");
      printf("Record count: %d\n", default_record_list->count);
      fflush(stdout);
      struct string_list* default_field_name_list = getFieldIds(message, getRecord(message, default_record_list, 0));
      printf("Field name count: %d\n", default_field_name_list->count);
      printf("Length of longest field name: %d\n", default_field_name_list->max_length);
      for (int i = 0; i < default_field_name_list->count; i++)
      {
          printf("Field name: %s\n", default_field_name_list->strings[i]);
      }
      fflush(stdout);
      //struct field_list* default_field_list = getFields(message, default_record_list->records[0]);
      struct field *testField = getField(message, getRecord(message, default_record_list, 0), "initial-value");
      struct field *testField2 = getField(message, getRecord(message, default_record_list, 0), "string-test");
      const char * testFieldId = getFieldId(message, testField);
      const char *testFieldId2 = getFieldId(message, testField2);
      printf("Test field id: %s\n", testFieldId);
      printf("Test field id 2: %s\n", testFieldId2);
      fflush(stdout);
      const char *testFieldType = getFieldType(message, testField);
      const char *testFieldType2 = getFieldType(message, testField2);
      printf("Test field type: %s\n", testFieldType);
      printf("Test field type 2: %s\n", testFieldType2);
      fflush(stdout);
      struct field_value *testFieldValue = getFieldValue(message, testField);
      int integerFieldValue = fieldValueAsInteger(message, testFieldValue);
      printf("Field integer value is %d\n", integerFieldValue);
      struct field_value *testFieldValue2 = getFieldValue(message, testField2);
      const char* stringFieldValue = fieldValueAsString(message, testFieldValue2);
      printf("Field string value 2 is: %s\n", stringFieldValue);
      printf("Leaving our test!");
      fflush(stdout);
      return;
  }

