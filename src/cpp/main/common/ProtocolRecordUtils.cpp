#include "ProtocolRecordUtils.h"

#include <jni.h>


/**
Constructor for a ProtocolRecordUtils object.
*/
ProtocolRecordUtils::ProtocolRecordUtils(JNIEnv *jvm, jobject protocolRecord, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, protocolRecord, typeUtils, listUtils);
    this->loadMethodIds();
}

ProtocolRecordUtils::~ProtocolRecordUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
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
jobject ProtocolRecordUtils::getProtocolRecords(const char *method, const char *key, const char *val)
{
    if (strcmp(method, "getRecords") == 0)
    {
        return this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsMethodId);
    }
    else if (strcmp(method, "getRecordsByCollection") == 0)
    {
        jstring javaKey = this->typeUtils->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByCollectionMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByTransformation") == 0)
    {
        jstring javaKey = this->typeUtils->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByTransformationMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByUUID") == 0)
    {
        jstring javaKey = this->typeUtils->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByUUIDMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByClassifier") == 0)
    {
        jstring javaKey = this->typeUtils->toJavaString(key);
        jstring javaVal = this->typeUtils->toJavaString(val);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByClassifierMethodId, javaKey, javaVal);
        this->jvm->DeleteLocalRef(javaKey);
        this->jvm->DeleteLocalRef(javaVal);
        return protocolRecords;
    }
    else
    {
        return NULL;
    }
}

struct record_list *ProtocolRecordUtils::getRecords(const char *recordMethod, const char *key, const char *val)
{
    jobject jprotocolRecords = this->getProtocolRecords(recordMethod, key, val);
    int recordCount = this->listUtils->getListLength(jprotocolRecords);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jprotocolRecords;

    return record_list;
}

struct record *ProtocolRecordUtils::getRecord(struct record_list *record_list, int index)
{
    jobject jrecord = this->jvm->CallObjectMethod(record_list->jrecords, this->listUtils->getListItemMethod(), index);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

void ProtocolRecordUtils::loadGlobalRefs(JNIEnv *jvm, jobject protocolRecord, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->protocolRecord = protocolRecord;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void ProtocolRecordUtils::loadMethodIds()
{
    jclass protocolRecordClass = JniUtils::getObjectClass(this->jvm, this->protocolRecord);
    this->getRecordsMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecords", this->getMethodSignature("getRecords"), false);
    this->getRecordsByCollectionMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByCollection", this->getMethodSignature("getRecordsByCollection"), false);
    this->getRecordsByUUIDMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByUUID", this->getMethodSignature("getRecordsByUUID"), false);
    this->getRecordsByTransformationMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByTransformation", this->getMethodSignature("getRecordsByTransformation"), false);
    this->getRecordsByClassifierMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByClassifier", this->getMethodSignature("getRecordsByClassifier"), false);
    this->jvm->DeleteLocalRef(protocolRecordClass);
}

const char *ProtocolRecordUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getRecords") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecordsByCollection") == 0)
    {
        return "(Ljava/lang/String;)Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecordsByUUID") == 0)
    {
        return "(Ljava/lang/String;)Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecordsByTransformation") == 0)
    {
        return "(Ljava/lang/String;)Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecordsByClassifier") == 0)
    {
        return "(Ljava/lang/String;Ljava/lang/Object;)Ljava/util/List;";
    }
    return NULL;
}
