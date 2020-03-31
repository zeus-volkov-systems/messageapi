#include "MessageApiEndpoint.h"

#include <iostream>
#include <string>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Constructor for the MessageApiEndpoint object. Takes a JNI environment pointer, an endpoint context (this refers to
the endpoint class that's instantiating the object), and a protocol record which holds containers of records.
*/
MessageApiEndpoint::MessageApiEndpoint(JNIEnv *env, jobject jendpoint, jobject jprotocolRecord)
{
    jvm = env;
    endpoint = jvm->NewGlobalRef(jendpoint);
    protocolRecord = jvm->NewGlobalRef(jprotocolRecord);

    java_util_List = static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass("java/util/List")));
    java_util_List_size = jvm->GetMethodID(java_util_List, "size", "()I");
    java_util_List_get = jvm->GetMethodID(java_util_List, "get", "(I)Ljava/lang/Object;");
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        jvm->DeleteGlobalRef(endpoint);
        jvm->DeleteGlobalRef(protocolRecord);
        jvm->DeleteGlobalRef(java_util_List);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what(); // information from length_error printed
    }
}

void MessageApiEndpoint::checkAndThrow(const char *errorMessage)
{
    if (jvm->ExceptionCheck())
    {
        std::cout << "MessageApiEndpoint threw the following exception:" << errorMessage << std::endl;
        jclass Exception = jvm->FindClass("java/lang/Exception");
        jvm->ThrowNew(Exception, errorMessage);
    }
}

JNIEnv * MessageApiEndpoint::getJVM()
{
    return jvm;
}

jclass MessageApiEndpoint::getNamedClass(const char *className)
{
    jclass clazz = jvm->FindClass(className);
    const char *msg = "getNamedClass> failed.";
    checkAndThrow(msg);
    return clazz;
}

jclass MessageApiEndpoint::getObjectClass(jobject obj)
{
    jobject objRef = jvm->NewLocalRef(obj);
    jclass clazz = jvm->GetObjectClass(objRef);
    jvm->DeleteLocalRef(objRef);
    return clazz;
}

jmethodID MessageApiEndpoint::getMethod(jclass clazz, const char *name, const char *signature, bool isStatic)
{
    jmethodID id = NULL;
    if (isStatic)
    {
        id = jvm->GetStaticMethodID(clazz, name, signature);
    }
    else
    {
        id = jvm->GetMethodID(clazz, name, signature);
    }

    const char *msg = "getMethod> jMethodID lookup failed.";
    checkAndThrow(msg);
    return id;
}

jstring MessageApiEndpoint::toJavaString(const char *s)
{
    return jvm->NewStringUTF(s);
}

const char * MessageApiEndpoint::fromJavaString(jstring s)
{
    const char *tempStr = jvm->GetStringUTFChars(s, NULL);
    int tempLen = strlen(tempStr);
    char *cStr = (char *)malloc((tempLen + 1) * sizeof(char));
    strcpy(cStr, tempStr);
    jvm->ReleaseStringUTFChars(s, tempStr);
    return cStr;
}

/**
 * 
 */
const char * MessageApiEndpoint::getRecordMethodSignature(const char* methodName)
{
    if (methodName == "getRecords")
    {
        return "()Ljava/util/List;";
    }
    else if (methodName == "getRecordsByCollection" || methodName == "getRecordsByUUID" || methodName == "getRecordsByTransformation")
    {
        return "(Ljava/lang/String;)Ljava/util/List;";
    }
    else if (methodName == "getRecordsByClassifier")
    {
        return "(Ljava/lang/String;Ljava/lang/Object;)Ljava/util/List;";
    }
    return NULL;
}

const char * MessageApiEndpoint::getFieldMethodSignature(const char *methodName)
{
    if (methodName == "getFieldIds")
    {
        return "()Ljava/util/List;";
    }
    else if (methodName == "getFields")
    {
        return "()Ljava/util/List;";
    }
    else if (methodName == "getField")
    {
        return "(Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/IField;";
    }
    else if (methodName == "getId")
    {
        return "()Ljava/lang/String;";
    }
    else if (methodName == "getType")
    {
        return "()Ljava/lang/String;";
    }
    else if (methodName == "getValue")
    {
        return "()Ljava/lang/Object;";
    }
    else if (methodName == "isValid")
    {
        return "()Z";
    }
    else if (methodName == "isRequired")
    {
        return "()Z";
    }
    return NULL;
}

/**
 * Factored method that handles all wrapped record retrieval methods including getRecords, getRecordsByCollection, getRecordsByTransformation,
 * getRecordsByClassifier, and getRecordsbyUUID.
 * This method takes a protocol reference which refers to the instance of the ProtocolRecord container as a java object,
 * a methodId as a java method id that refers to the particular method instance, a method name as a string (const char pointer), and additional
 * paramters of key and value as const char strings. The key and value arguments may or may not be used depending on the particular method called
 * (referred to by the methodId). This method returns a protocolRecords java object that represents the return from the associated java object.
 * To be used in a native context, this return object must be unpacked.
 */
jobject MessageApiEndpoint::getProtocolRecords(jobject protocolref, jmethodID methodId, const char* method, const char* key, const char* val)
{
    if (method == "getRecords")
    {
        return jvm->CallObjectMethod(protocolref, methodId);
    }
    jstring javaKey = toJavaString(key);
    jobject protocolRecords;
    if (method == "getRecordsByCollection" || method == "getRecordsByTransformation" || method == "getRecordsByUUID")
    {
        protocolRecords = jvm->CallObjectMethod(protocolref, methodId, javaKey);
    }
    else if (method == "getRecordsByClassifier")
    {
        jstring javaVal = toJavaString(val);
        protocolRecords = jvm->CallObjectMethod(protocolref, methodId, javaKey, javaVal);
        jvm->DeleteLocalRef(javaVal);
    }
    jvm->DeleteLocalRef(javaKey);
    return protocolRecords;
}

struct record_list * MessageApiEndpoint::getRecords(const char *recordMethod, const char *key, const char *val)
{
    jobject protocolRecordRef = jvm->NewLocalRef(protocolRecord);
    jclass protocolRecordClass = getObjectClass(protocolRecordRef);
    jmethodID methodId = getMethod(protocolRecordClass, recordMethod, getRecordMethodSignature(recordMethod), false);

    jobject jprotocolRecords = getProtocolRecords(protocolRecordRef, methodId, recordMethod, key, val);

    int recordCount = jvm->CallIntMethod(jprotocolRecords, java_util_List_size);
    record** records = (record**)malloc(sizeof(record*) * recordCount);
    for (int i = 0; i < recordCount; i++) {
        jobject jrecord = static_cast<jobject>(jvm->CallObjectMethod(jprotocolRecords, java_util_List_get, i));
        record *record = (struct record*) malloc(sizeof(struct record) + sizeof(jrecord));
        record->jrecord = (jobject) jrecord;
        records[i] = record;
    }
    struct record_list *record_list = (struct record_list*) malloc(sizeof(struct record_list) + sizeof(records));
    record_list->count = recordCount;
    record_list->records = records;

    jvm->DeleteLocalRef(jprotocolRecords);
    jvm->DeleteLocalRef(protocolRecordClass);
    jvm->DeleteLocalRef(protocolRecordRef);

    return record_list;
}

struct string_list * MessageApiEndpoint::getFieldIds(struct record *record) {
    const char *methodName = "getFieldIds";

    jobject jRecordRef = jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldIdMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);
    jobject jFieldIdList = jvm->CallObjectMethod(jRecordRef, jFieldIdMethodId);

    int fieldCount = jvm->CallIntMethod(jFieldIdList, java_util_List_size);
    char **fieldIds = (char**) malloc(sizeof(char*) * fieldCount);

    int maxFieldIdLength = 0;
    for (int i = 0; i < fieldCount; i++) {
        jstring fieldId = static_cast<jstring>(jvm->CallObjectMethod(jFieldIdList, java_util_List_get, i));
        const char *tempFieldId = jvm->GetStringUTFChars(fieldId, NULL);
        int tempMaxFieldIdLength = strlen(tempFieldId);
        if (tempMaxFieldIdLength > maxFieldIdLength) {
            maxFieldIdLength = tempMaxFieldIdLength;
        }
        fieldIds[i] = (char*) malloc((tempMaxFieldIdLength+1) * sizeof(char));
        strcpy(fieldIds[i], tempFieldId);
        jvm->ReleaseStringUTFChars(fieldId, tempFieldId);
        jvm->DeleteLocalRef(fieldId);
    }

    struct string_list *field_names = (struct string_list*) malloc(sizeof(struct string_list) + sizeof(fieldIds));
    field_names->max_length = maxFieldIdLength;
    field_names->count = fieldCount;
    field_names->strings = fieldIds;

    jvm->DeleteLocalRef(jFieldIdList);
    jvm->DeleteLocalRef(jRecordClass);
    jvm->DeleteLocalRef(jRecordRef);

    return field_names;
}

struct field_list * MessageApiEndpoint::getFields(struct record *record) {
    const char* methodName = "getFields";

    jobject jRecordRef = jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jobject jFieldList = jvm->CallObjectMethod(jRecordRef, jFieldMethodId);

    int fieldCount = jvm->CallIntMethod(jFieldList, java_util_List_size);
    struct field **fields = (struct field**)malloc(sizeof(struct field*) * fieldCount);

    for (int i = 0; i < fieldCount; i++) {
        jobject jfield = static_cast<jobject>(jvm->CallObjectMethod(jFieldList, java_util_List_get, i));
        struct field *field = (struct field*)malloc(sizeof(field) + sizeof(jfield));
        field->jfield = (jobject)jfield;
        fields[i] = field;
    }

    struct field_list *field_list = (struct field_list*)malloc(sizeof(struct field_list) + sizeof(fields));
    field_list->count = fieldCount;
    field_list->fields = fields;

    jvm->DeleteLocalRef(jRecordClass);
    jvm->DeleteLocalRef(jRecordRef);

    return field_list;

}

struct field * MessageApiEndpoint::getField(struct record *record, const char* fieldId) {
    const char *methodName = "getField";

    jobject jRecordRef = jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldId = toJavaString(fieldId);
    jobject jField = jvm->CallObjectMethod(jRecordRef, jFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(field) + sizeof(jField));
    field->jfield = jField;

    jvm->DeleteLocalRef(jFieldId);
    jvm->DeleteLocalRef(jRecordClass);
    jvm->DeleteLocalRef(jRecordRef);

    return field;
}

const char * MessageApiEndpoint::getFieldId(struct field *field) {
    const char *methodName = "getId";

    jobject jFieldRef = jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldId = static_cast<jstring>(jvm->CallObjectMethod(jFieldRef, jFieldMethodId));
    const char * fieldId = this->fromJavaString(jFieldId);

    jvm->DeleteLocalRef(jFieldId);
    jvm->DeleteLocalRef(jFieldRef);

    return fieldId;
}

const char * MessageApiEndpoint::getFieldType(struct field *field)
{
    const char *methodName = "getType";

    jobject jFieldRef = jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldType = static_cast<jstring>(jvm->CallObjectMethod(jFieldRef, jFieldMethodId));
    const char *fieldType = this->fromJavaString(jFieldType);

    jvm->DeleteLocalRef(jFieldType);
    jvm->DeleteLocalRef(jFieldRef);

    return fieldType;
}

void * MessageApiEndpoint::getFieldValue(struct field *field)
{
    const char *methodName = "getValue";

    jobject jFieldRef = jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jobject jFieldValue = jvm->CallObjectMethod(jFieldRef, jFieldMethodId);

    void *value = &jFieldValue;

    jvm->DeleteLocalRef(jRecordClass);
    jvm->DeleteLocalRef(jFieldRef);

    return value;
}

bool MessageApiEndpoint::getFieldIsValid(struct field *field)
{
    const char *methodName = "isValid";

    jobject jFieldRef = jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jvm->DeleteLocalRef(jFieldRef);
}

bool MessageApiEndpoint::getFieldIsRequired(struct field *field)
{
    const char *methodName = "isRequired";

    jobject jFieldRef = jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jvm->DeleteLocalRef(jFieldRef);
}
