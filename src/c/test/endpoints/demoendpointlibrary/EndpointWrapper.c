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
      struct string_list* default_field_name_list = getFieldNames(message, default_record_list->records[0]);
      printf("Field name count: %d\n", default_field_name_list->count);
      printf("Length of longest field name: %d\n", default_field_name_list->max_length);
      for (int i = 0; i < default_field_name_list->count; i++)
      {
          printf("Field name: %s\n", default_field_name_list->strings[i]);
      }
      fflush(stdout);
      struct field_list* default_field_list = getFields(message, default_record_list->records[0]);
      /*for (int i = 0; i < default_record_list->count; i++) {
          struct string_list* record_field_names = getRecordFieldNames(message,)
          for (int j = 0; j < )
          printf("Record Type: %s\n", getRecordType(default_record_list->records[i]));
      }*/
      printf("Leaving our test!");
      fflush(stdout);
      return;
  }

