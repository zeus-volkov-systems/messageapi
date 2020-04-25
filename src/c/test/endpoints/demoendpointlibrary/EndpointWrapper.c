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
      for (int i = 0; i < default_field_name_list->count; i++) {
          printf("Field name: %s\n", default_field_name_list->strings[i]);
      }
      fflush(stdout);
      //struct field_list* default_field_list = getFields(message, default_record_list->records[0]);
      struct field *testField = getField(message, getRecord(message, default_record_list, 0), "initial-value");
      struct field *testField2 = getField(message, getRecord(message, default_record_list, 0), "string-test");
      struct field *testField3 = getField(message, getRecord(message, default_record_list, 0), "int-list-test");
      struct field *testField4 = getField(message, getRecord(message, default_record_list, 0), "null-test");
      const char *testFieldId = getFieldId(message, testField);
      const char *testFieldId2 = getFieldId(message, testField2);
      const char *testFieldId3 = getFieldId(message, testField3);
      const char *testFieldId4 = getFieldId(message, testField4);
      printf("Test field 1 id: %s\n", testFieldId);
      printf("Test field 2 id: %s\n", testFieldId2);
      printf("Test field 3 id: %s\n", testFieldId3);
      printf("Test field 3 id: %s\n", testFieldId3);
      printf("Test field 4 id: %s\n", testFieldId4);
      fflush(stdout);
      const char *testFieldType = getFieldType(message, testField);
      const char *testFieldType2 = getFieldType(message, testField2);
      const char *testFieldType3 = getFieldType(message, testField3);
      const char *testFieldType4 = getFieldType(message, testField4);
      printf("Test field 1 type: %s\n", testFieldType);
      printf("Test field 2 type: %s\n", testFieldType2);
      printf("Test field 3 type: %s\n", testFieldType3);
      printf("Test field 4 type: %s\n", testFieldType4);
      fflush(stdout);
      struct value *testFieldValue = getFieldVal(message, testField);
      int integerFieldValue = valAsInt(message, testFieldValue);
      printf("Field integer value is %d\n", integerFieldValue);
      struct value *testFieldValue2 = getFieldVal(message, testField2);
      const char *stringFieldValue = valAsString(message, testFieldValue2);
      printf("Field string value 2 is: %s\n", stringFieldValue);
      struct value *testFieldValue3 = getFieldVal(message, testField3);
      struct val_list *val_list = valAsList(message, testFieldValue3);
      printf("Field value 3 (list) length is: %d\n", val_list->count);
      for (int i = 0; i < val_list->count; i++) {
          printf("Field value 3, element %d, is: %d\n", i, getIntEntry(message, val_list, i));
      }
      fflush(stdout);
      struct value *testFieldValue4 = getFieldVal(message, testField4);
      if (valIsNull(message, testFieldValue4)) {
          printf("Got a null field val.\n");
      } else {
          printf("Field val has a value!\n");
      }
      fflush(stdout);
      struct record *returnRecord = createRecord(message);
      struct string_list *fieldIds = getFieldIds(message, returnRecord);
      printf("field ids for return field follow. \n");
      for (int i=0; i < fieldIds->count; i++) {
          printf("Field name: %s\n", fieldIds->strings[i]);
          if (valIsNull(message, getFieldVal(message, getField(message, returnRecord,fieldIds->strings[i]))))
          {
              printf("Got a null field val for %s.\n", fieldIds->strings[i]);
              setIntVal(message, getField(message, returnRecord, fieldIds->strings[i]), 5);
          }
          else
          {
              printf("Field val for field %s has a value!\n", fieldIds->strings[i]);
          }
      }
      printf("Leaving our C test!");
      fflush(stdout);
      struct packet* packet = createPacket(message);
      addPacketRecord(message, packet, returnRecord);
      return packet->jpacket;
  }

