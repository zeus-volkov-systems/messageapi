#include "MessageApiEndpoint.h"

#include <iostream>
#include <string>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**

*/
MessageApiEndpoint::MessageApiEndpoint(JNIEnv *env, jobject jendpoint, jobject jprotocolRecord)
{
    jvm = env;
    endpoint = jvm->NewGlobalRef(jendpoint);
    protocolRecord = jvm->NewGlobalRef(jprotocolRecord);
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        jvm->DeleteGlobalRef(endpoint);
        jvm->DeleteGlobalRef(protocolRecord);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what(); // information from length_error printed
    }
}

void MessageApiEndpoint::checkAndThrow(const char *msg)
{
    if (jvm->ExceptionCheck())
    {
        std::cout << "MessageApiEndpoint::checkAndThrow> msg=" << msg << std::endl;
        jclass Exception = jvm->FindClass("java/lang/Exception");
        jvm->ThrowNew(Exception, msg);
    }
}

JNIEnv *MessageApiEndpoint::getJVM()
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

const char* MessageApiEndpoint::fromJavaString(jstring s)
{
    const char *tempStr = jvm->GetStringUTFChars(s, NULL);
    int tempLen = strlen(tempStr);
    char *cStr = (char *)malloc((tempLen + 1) * sizeof(char));
    strcpy(cStr, tempStr);
    jvm->ReleaseStringUTFChars(s, tempStr);
    return cStr;
}

const char* MessageApiEndpoint::getRecordMethodSignature(const char* method)
{
    if (method == "getRecords")
    {
        return "()Ljava/util/List;";
    }
    else if (method == "getRecordsByCollection" || method == "getRecordsByUUID" || method == "getRecordsByTransformation")
    {
        return "(Ljava/lang/String;)Ljava/util/List;";
    }
    else if (method == "getRecordsByClassifier")
    {
        return "(Ljava/lang/String;Ljava/lang/Object;)Ljava/util/List;";
    }
    return NULL;
}

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

struct records_vector* MessageApiEndpoint::getRecords(const char* recordMethod, const char* key, const char* val)
{
    static jclass java_util_List;
    jmethodID java_util_List_size;
    jmethodID java_util_List_get;
    java_util_List = static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass("java/util/List")));
    java_util_List_size = jvm->GetMethodID(java_util_List, "size", "()I");
    java_util_List_get = jvm->GetMethodID(java_util_List, "get", "(I)Ljava/lang/Object;");

    jobject protocolRecordRef = jvm->NewLocalRef(protocolRecord);
    jclass protocolRecordClass = getObjectClass(protocolRecordRef);
    jmethodID methodId = getMethod(protocolRecordClass, recordMethod, getRecordMethodSignature(recordMethod), false);

    jobject jprotocolRecords = getProtocolRecords(protocolRecordRef, methodId, recordMethod, key, val);

    int recordCount = jvm->CallIntMethod(jprotocolRecords, java_util_List_size);
    jobject** jrecords = (jobject**)malloc(sizeof(jobject*) * recordCount);
    for (int i = 0; i < recordCount; i++) {
        jobject jrecord = static_cast<jobject>(jvm->CallObjectMethod(jprotocolRecords, java_util_List_get, i));
        jrecords[i] = (jobject*) jrecord;
        jvm->DeleteLocalRef(jrecord);
    }

    struct records_vector *vector = (struct records_vector*) malloc(sizeof(struct records_vector) + sizeof(jrecords));
    vector->count = recordCount;
    vector->records = jrecords;

    jvm->DeleteLocalRef(protocolRecordRef);
    jvm->DeleteLocalRef(protocolRecordClass);

    return vector;
}

/*struct string_vector* MessageApiEndpoint::getTransformations() {
    static jclass java_util_List;
    jmethodID java_util_List_size;
    jmethodID java_util_List_get;
    java_util_List = static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass("java/util/List")));
    java_util_List_size = jvm->GetMethodID(java_util_List, "size", "()I");
    java_util_List_get = jvm->GetMethodID(java_util_List, "get", "(I)Ljava/lang/Object;");
    
    jobject arrayList = getObject(key);
    int count = jvm->CallIntMethod(arrayList, java_util_List_size);
    char **strings = (char**) malloc(sizeof(char*) * count);
	int length = 0;
	for (int i = 0; i < count; i++) {
  		jstring element = static_cast<jstring>(jvm->CallObjectMethod(arrayList, java_util_ArrayList_get, i));
  		const char* tempStr = jvm->GetStringUTFChars(element, NULL);
		int tempLen = strlen(tempStr);
		if (tempLen > length) {
			length = tempLen;
		}
		strings[i] = (char*) malloc((tempLen+1) * sizeof(char));
		strcpy(strings[i], tempStr);
  		jvm->ReleaseStringUTFChars(element, tempStr);
  		jvm->DeleteLocalRef(element);
	}
	struct string_vector *vector = (struct string_vector*) malloc(sizeof(struct string_vector) + sizeof(strings));
	vector->max_length = length;
	vector->count = count;
	vector->strings = strings;
    jvm->DeleteGlobalRef(java_util_ArrayList);
	return vector;
}*/

/*jobject NativeTask::getObject(const char* key) {
	jstring javaKey = toJavaString(key);
    jobject objRef = jvm->NewLocalRef(data);
    jclass clazz = getObjectClass(objRef);
    jmethodID mid = getMethod(clazz, "get", "(Ljava/lang/String;)Ljava/lang/Object;", false);
	jobject retVal = jvm->CallObjectMethod(objRef, mid, javaKey);
    jvm->DeleteLocalRef(javaKey);
    jvm->DeleteLocalRef(objRef);
    jvm->DeleteLocalRef(clazz);
    return retVal;
}*/

/*void NativeTask::addStringArrayList(const char *key, char **strings, int length, int count)
{
    static jclass java_util_ArrayList;
    static jmethodID java_util_ArrayList_;
    jmethodID java_util_ArrayList_size;
    jmethodID java_util_ArrayList_get;
    jmethodID java_util_ArrayList_add;

    java_util_ArrayList = static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass("java/util/ArrayList")));
    java_util_ArrayList_ = jvm->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
    java_util_ArrayList_size = jvm->GetMethodID(java_util_ArrayList, "size", "()I");
    java_util_ArrayList_get = jvm->GetMethodID(java_util_ArrayList, "get", "(I)Ljava/lang/Object;");
    java_util_ArrayList_add = jvm->GetMethodID(java_util_ArrayList, "add", "(Ljava/lang/Object;)Z");

    jobject result = jvm->NewObject(java_util_ArrayList, java_util_ArrayList_, count);
    for (int i = 0; i < count; i++)
    {
        jstring element = toJavaString(strings[i]);
        jvm->CallBooleanMethod(result, java_util_ArrayList_add, element);
        jvm->DeleteLocalRef(element);
    }
    addObject(key, result);
    jvm->DeleteLocalRef(result);
    jvm->DeleteGlobalRef(java_util_ArrayList);
}*/