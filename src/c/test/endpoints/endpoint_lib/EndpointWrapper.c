#include <jni.h>
#include <stdio.h>
#include "messageapi_structs.h"
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
      record_list* default_record_list = getRecords(message);
      //struct record_list* classifier_record_list = getRecordsByClassifier(message, "color", "blue");
      //struct record_list* collection_record_list = getRecordsByCollection(message, "gold");
      //struct record_list* transformation_record_list = getRecordsByTransformation(message, "combine-colors");
      printf("Record count: %d\n", default_record_list->count);
      string_list* default_field_name_list = getFieldIds(message, getRecord(message, default_record_list, 0));
      printf("Field name count: %d\n", default_field_name_list->count);
      printf("Length of longest field name: %d\n", default_field_name_list->max_length);
      for (int i = 0; i < default_field_name_list->count; i++) {
          printf("Field name: %s\n", default_field_name_list->strings[i]);
      }
      fflush(stdout);
      field *testField = getField(message, getRecord(message, default_record_list, 0), "initial-value");
      field *testField2 = getField(message, getRecord(message, default_record_list, 0), "string-test");
      field *testField3 = getField(message, getRecord(message, default_record_list, 0), "int-list-test");
      field *testField4 = getField(message, getRecord(message, default_record_list, 0), "null-test");
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
      int integerFieldValue = getFieldIntVal(message, testField);
      printf("Field integer value is %d\n", integerFieldValue);
      const char *stringFieldValue = getFieldStringVal(message, testField2);
      printf("Field string value 2 is: %s\n", stringFieldValue);
      val_list *fieldList = getFieldListVal(message, testField3);
      printf("Field value 3 (list) length is: %d\n", fieldList->count);
      for (int i = 0; i < fieldList->count; i++)
      {
          printf("Field value 3, element %d, is: %d\n", i, getIntItem(message, fieldList, i));
      }
      fflush(stdout);
      if (getFieldIsNull(message, testField4)) {
          printf("Got a null field val for field 4.\n");
      } else {
          printf("Field val 4 has a value!\n");
      }
      fflush(stdout);
      record *returnRecord = createRecord(message);
      string_list *fieldIds = getFieldIds(message, returnRecord);
      printf("field ids for return field follow. \n");
      for (int i=0; i < fieldIds->count; i++) {
          printf("Field name: %s\n", fieldIds->strings[i]);
          if (getFieldIsNull(message, getField(message, returnRecord,fieldIds->strings[i])))
          {
              printf("Got a null field val for %s.\n", fieldIds->strings[i]);
              setFieldIntVal(message, getField(message, returnRecord, fieldIds->strings[i]), 5);
          }
          else
          {
              printf("Field val for field %s already has a value!\n", fieldIds->strings[i]);
          }
      }
      fflush(stdout);
      printf("Creating a value list to hold strings..\n");
      val_list *returnList = createList(message);
      addStringItem(message, returnList, "first element of our string!");
      addStringItem(message, returnList, "second element of our string!!");
      printf("Created a string list.\n");
      setFieldListVal(message, getField(message, returnRecord, "return-list"), returnList);
      printf("First value added to the return-list field: %s\n", getStringItem(message, returnList, 0));
      printf("Second value added to the return-list field: %s\n", getStringItem(message, returnList, 1));
      printf("Added the string list to the return record. Should have two elements, see above.\n");
      fflush(stdout);
      packet* packet = createPacket(message);
      addPacketRecord(message, packet, returnRecord);
      printf("Leaving our C test!");
      fflush(stdout);
      return packet->jpacket;
  }

