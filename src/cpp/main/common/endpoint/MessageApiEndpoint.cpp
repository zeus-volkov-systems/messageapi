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
    this->jvm = env;
    this->endpoint = this->jvm->NewGlobalRef(jendpoint);
    this->protocolRecord = this->jvm->NewGlobalRef(jprotocolRecord);
    this->jException = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Exception")));

    this->loadGlobalClassRefs();

    this->loadEndpointMethodIds();
    this->loadPacketMethodIds();
    this->loadProtocolRecordMethodIds();
    this->loadRecordMethodIds();
    this->loadRejectionMethodIds();
    this->loadFieldMethodIds();
    this->loadConditionMethodIds();
    this->loadValueTypeMethodIds();
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        this->jvm->DeleteGlobalRef(this->jArrayListClass);
        this->jvm->DeleteGlobalRef(this->jIntClass);
        this->jvm->DeleteGlobalRef(this->jLongClass);
        this->jvm->DeleteGlobalRef(this->jFloatClass);
        this->jvm->DeleteGlobalRef(this->jDoubleClass);
        this->jvm->DeleteGlobalRef(this->jByteClass);
        this->jvm->DeleteGlobalRef(this->jStringClass);
        this->jvm->DeleteGlobalRef(this->jBoolClass);
        this->jvm->DeleteGlobalRef(this->jShortClass);
        this->jvm->DeleteGlobalRef(this->endpoint);
        this->jvm->DeleteGlobalRef(this->protocolRecord);
        this->jvm->DeleteGlobalRef(this->jException);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void MessageApiEndpoint::loadGlobalClassRefs()
{
    this->jIntClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Integer")));
    this->jLongClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Long")));
    this->jFloatClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Float")));
    this->jDoubleClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Double")));
    this->jByteClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Byte")));
    this->jStringClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/String")));
    this->jBoolClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Boolean")));
    this->jShortClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/lang/Short")));
    this->jArrayListClass = static_cast<jclass>(this->jvm->NewGlobalRef(this->jvm->FindClass("java/util/ArrayList")));
}

void MessageApiEndpoint::loadPacketMethodIds()
{
    jclass packetClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IPacket");
    this->setPacketRecordsMethodId = this->getMethod(packetClass, "setRecords", this->getPacketMethodSignature("setRecords"), false);
    this->addPacketRecordMethodId = this->getMethod(packetClass, "addRecord", this->getPacketMethodSignature("addRecord"), false);
    this->addPacketRecordsMethodId = this->getMethod(packetClass, "addRecords", this->getPacketMethodSignature("addRecords"), false);
    this->setPacketRejectionsMethodId = this->getMethod(packetClass, "setRejections", this->getPacketMethodSignature("setRejections"), false);
    this->addPacketRejectionMethodId = this->getMethod(packetClass, "addRejection", this->getPacketMethodSignature("addRejection"), false);
    this->addPacketRejectionsMethodId = this->getMethod(packetClass, "addRejections", this->getPacketMethodSignature("addRejections"), false);
    this->getPacketRecordsMethodId = this->getMethod(packetClass, "getRecords", this->getPacketMethodSignature("getRecords"), false);
    this->getPacketRejectionsMethodId = this->getMethod(packetClass, "getRejections", this->getPacketMethodSignature("getRejections"), false);
    this->jvm->DeleteLocalRef(packetClass);
}

void MessageApiEndpoint::loadEndpointMethodIds()
{

    jclass endpointClass = this->getObjectClass(this->endpoint);
    this->getStateContainerMethodId = this->getMethod(endpointClass, "getStateContainer", this->getEndpointMethodSignature("getStateContainer"), false);
    this->getDefaultFieldsMethodId = this->getMethod(endpointClass, "getDefaultFields", this->getEndpointMethodSignature("getDefaultFields"), false);
    this->createPacketMethodId = this->getMethod(endpointClass, "createPacket", this->getEndpointMethodSignature("createPacket"), false);
    this->createRecordMethodId = this->getMethod(endpointClass, "createRecord", this->getEndpointMethodSignature("createRecord"), false);
    this->createRejectionMethodId = this->getMethod(endpointClass, "createRejection", this->getEndpointMethodSignature("createRejection"), false);
    this->jvm->DeleteLocalRef(endpointClass);
}

void MessageApiEndpoint::loadProtocolRecordMethodIds()
{

    jclass protocolRecordClass = this->getObjectClass(this->protocolRecord);
    this->getRecordsMethodId = this->getMethod(protocolRecordClass, "getRecords", this->getProtocolRecordMethodSignature("getRecords"), false);
    this->getRecordsByCollectionMethodId = this->getMethod(protocolRecordClass, "getRecordsByCollection", this->getProtocolRecordMethodSignature("getRecordsByCollection"), false);
    this->getRecordsByUUIDMethodId = this->getMethod(protocolRecordClass, "getRecordsByUUID", this->getProtocolRecordMethodSignature("getRecordsByUUID"), false);
    this->getRecordsByTransformationMethodId = this->getMethod(protocolRecordClass, "getRecordsByTransformation", this->getProtocolRecordMethodSignature("getRecordsByTransformation"), false);
    this->getRecordsByClassifierMethodId = this->getMethod(protocolRecordClass, "getRecordsByClassifier", this->getProtocolRecordMethodSignature("getRecordsByClassifier"), false);
    this->jvm->DeleteLocalRef(protocolRecordClass);
}

void MessageApiEndpoint::loadRecordMethodIds()
{
    jclass recordClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IRecord");
    /*Intrinsic Methods*/
    this->getRecordIsValidMethodId = this->getMethod(recordClass, "isValid", this->getRecordMethodSignature("isValid"), false);
    this->getRecordCopyMethodId = this->getMethod(recordClass, "getCopy", this->getRecordMethodSignature("getCopy"), false);
    /*Field Related Methods*/
    this->getRecordFieldIdsMethodId = this->getMethod(recordClass, "getFieldIds", this->getRecordMethodSignature("getFieldIds"), false);
    this->getRecordFieldsMethodId = this->getMethod(recordClass, "getFields", this->getRecordMethodSignature("getFields"), false);
    this->getRecordHasFieldMethodId = this->getMethod(recordClass, "hasField", this->getRecordMethodSignature("hasField"), false);
    this->getRecordFieldMethodId = this->getMethod(recordClass, "getField", this->getRecordMethodSignature("getField"), false);
    /*Condition Related Methods*/
    this->getRecordConditionIdsMethodId = this->getMethod(recordClass, "getConditionIds", this->getRecordMethodSignature("getConditionIds"), false);
    this->getRecordConditionsMethodId = this->getMethod(recordClass, "getConditions", this->getRecordMethodSignature("getConditions"), false);
    this->getRecordHasConditionMethodId = this->getMethod(recordClass, "hasCondition", this->getRecordMethodSignature("hasCondition"), false);
    this->getRecordConditionMethodId = this->getMethod(recordClass, "getCondition", this->getRecordMethodSignature("getCondition"), false);
    this->jvm->DeleteLocalRef(recordClass);
}

void MessageApiEndpoint::loadRejectionMethodIds()
{
    jclass rejectionClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IRejection");
    this->getRejectionCopyMethodId = this->getMethod(rejectionClass, "getCopy", this->getRejectionMethodSignature("getCopy"), false);
    this->getRejectionReasonsMethodId = this->getMethod(rejectionClass, "getReasons", this->getRejectionMethodSignature("getReasons"), false);
    this->getRejectionRecordMethodId = this->getMethod(rejectionClass, "getRecord", this->getRejectionMethodSignature("getRecord"), false);
    this->addRejectionReasonMethodId = this->getMethod(rejectionClass, "addReason", this->getRejectionMethodSignature("addReason"), false);
    this->jvm->DeleteLocalRef(rejectionClass);
}

void MessageApiEndpoint::loadFieldMethodIds()
{
    jclass fieldClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IField");
    this->getFieldIdMethodId = this->getMethod(fieldClass, "getId", this->getFieldMethodSignature("getId"), false);
    this->getFieldTypeMethodId = this->getMethod(fieldClass, "getType", this->getFieldMethodSignature("getType"), false);
    this->getFieldValueMethodId = this->getMethod(fieldClass, "getValue", this->getFieldMethodSignature("getValue"), false);
    this->getFieldIsValidMethodId = this->getMethod(fieldClass, "isValid", this->getFieldMethodSignature("isValid"), false);
    this->getFieldIsRequiredMethodId = this->getMethod(fieldClass, "isRequired", this->getFieldMethodSignature("isRequired"), false);
    this->setFieldValueMethodId = this->getMethod(fieldClass, "setValue", this->getFieldMethodSignature("setValue"), false);
    this->jvm->DeleteLocalRef(fieldClass);
}

void MessageApiEndpoint::loadConditionMethodIds()
{
    jclass conditionClass = this->getNamedClass("gov/noaa/messageapi/interfaces/ICondition");
    this->getConditionIdMethodId = this->getMethod(conditionClass, "getId", this->getConditionMethodSignature("getId"), false);
    this->getConditionTypeMethodId = this->getMethod(conditionClass, "getType", this->getConditionMethodSignature("getType"), false);
    this->getConditionOperatorMethodId = this->getMethod(conditionClass, "getOperator", this->getConditionMethodSignature("getOperator"), false);
    this->getConditionValueMethodId = this->getMethod(conditionClass, "getValue", this->getConditionMethodSignature("getValue"), false);
    this->setConditionValueMethodId = this->getMethod(conditionClass, "setValue", this->getConditionMethodSignature("setValue"), false);
    this->jvm->DeleteLocalRef(conditionClass);
}

/**
 * Loads the default value types for MessageApiEndpoint.
 * Default types are relatively primitive data types. More complicated 'struct' types
 * will require extension of this by user methods.
 * The included default types have associated access,modification,and release methods.
 * Each also has an associated 'list' method (i.e., string has string_list, byte has byte_list, etc.)
 * Default types include the following:
 * integer, long, float, double, string, byte, boolean
 */
void MessageApiEndpoint::loadValueTypeMethodIds()
{
    jclass jListClass = this->getNamedClass("java/util/List");
    this->getJListSizeMethodId = this->jvm->GetMethodID(jListClass, "size", "()I");
    this->getJListItemMethodId = this->jvm->GetMethodID(jListClass, "get", "(I)Ljava/lang/Object;");
    this->addJListItemMethodId = this->jvm->GetMethodID(jListClass, "add", "(Ljava/lang/Object;)Z");
    this->jvm->DeleteLocalRef(jListClass);

    /*Initialization for list as ArrayList (not List)*/
    this->createJArrayListMethodId = this->jvm->GetMethodID(this->jArrayListClass, "<init>", "()V");

    jclass jBoolClass = this->getNamedClass("java/lang/Boolean");
    this->getJBoolMethodId = this->jvm->GetMethodID(jBoolClass, "booleanValue", "()Z");
    this->createJBoolMethodId = this->jvm->GetMethodID(jBoolClass, "<init>", "(Z)V");
    this->jvm->DeleteLocalRef(jBoolClass);

    jclass jByteClass = this->getNamedClass("java/lang/Byte");
    this->getJByteMethodId = this->jvm->GetMethodID(jByteClass, "byteValue", "()B");
    this->createJByteMethodId = this->jvm->GetMethodID(jByteClass, "<init>", "(B)V");
    this->jvm->DeleteLocalRef(jByteClass);

    jclass jIntClass = this->getNamedClass("java/lang/Integer");
    this->getJIntMethodId = this->jvm->GetMethodID(jIntClass, "intValue", "()I");
    this->createJIntMethodId = this->jvm->GetMethodID(jIntClass, "<init>", "(I)V");
    this->jvm->DeleteLocalRef(jIntClass);

    jclass jLongClass = this->getNamedClass("java/lang/Long");
    this->getJLongMethodId = this->jvm->GetMethodID(jLongClass, "longValue", "()J");
    this->createJLongMethodId = this->jvm->GetMethodID(jLongClass, "<init>", "(J)V");
    this->jvm->DeleteLocalRef(jLongClass);

    jclass jShortClass = this->getNamedClass("java/lang/Short");
    this->getJShortMethodId = this->jvm->GetMethodID(jShortClass, "shortValue", "()S");
    this->createJShortMethodId = this->jvm->GetMethodID(jShortClass, "<init>", "(S)V");
    this->jvm->DeleteLocalRef(jShortClass);

    jclass jFloatClass = this->getNamedClass("java/lang/Float");
    this->getJFloatMethodId = this->jvm->GetMethodID(jFloatClass, "floatValue", "()F");
    this->createJFloatMethodId = this->jvm->GetMethodID(jFloatClass, "<init>", "(F)V");
    this->jvm->DeleteLocalRef(jFloatClass);

    jclass jDoubleClass = this->getNamedClass("java/lang/Double");
    this->getJDoubleMethodId = this->jvm->GetMethodID(jDoubleClass, "doubleValue", "()D");
    this->createJDoubleMethodId = this->jvm->GetMethodID(jDoubleClass, "<init>", "(D)V");
    this->jvm->DeleteLocalRef(jDoubleClass);

}

/**
 * Default error handling for the MessageApiEndpoint Class.
 */
void MessageApiEndpoint::checkAndThrow(std::string errorMessage)
{
    if (this->jvm->ExceptionCheck())
    {
        std::cout << "MessageApiEndpoint.cpp errored with the following message:" << errorMessage << std::endl;
        this->jvm->ThrowNew(this->jException, errorMessage.c_str());
    }
}


jclass MessageApiEndpoint::getNamedClass(const char *className)
{
    jclass clazz = this->jvm->FindClass(className);
    const char *msg = "getNamedClass> failed.";
    std::string buf(msg);
    buf.append(className);
    checkAndThrow(buf);
    return clazz;
}

jclass MessageApiEndpoint::getObjectClass(jobject obj)
{
    jobject objRef = this->jvm->NewLocalRef(obj);
    jclass clazz = this->jvm->GetObjectClass(objRef);
    this->jvm->DeleteLocalRef(objRef);
    return clazz;
}

jmethodID MessageApiEndpoint::getMethod(jclass clazz, const char *name, const char *signature, bool isStatic)
{
    jmethodID id = NULL;
    if (isStatic)
    {
        id = this->jvm->GetStaticMethodID(clazz, name, signature);
    }
    else
    {
        id = this->jvm->GetMethodID(clazz, name, signature);
    }

    const char *msg = "getMethod> jMethodID lookup failed.";
    std::string buf(msg);
    buf.append(name);
    checkAndThrow(buf);
    return id;
}

jstring MessageApiEndpoint::toJavaString(const char *s)
{
    return this->jvm->NewStringUTF(s);
}

const char * MessageApiEndpoint::fromJavaString(jstring s)
{
    const char *tempStr = this->jvm->GetStringUTFChars(s, NULL);
    int tempLen = strlen(tempStr);
    char *cStr = (char *)malloc((tempLen + 1) * sizeof(char));
    strcpy(cStr, tempStr);
    this->jvm->ReleaseStringUTFChars(s, tempStr);
    return cStr;
}

const char *MessageApiEndpoint::getEndpointMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getStateContainer") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName,"getDefaultFields") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "createPacket") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IPacket;";
    }
    else if (strcmp(methodName, "createRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "createRejection") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRecord;Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/IRejection;";
    }
    return NULL;
}

const char *MessageApiEndpoint::getPacketMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "setRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "addRecord") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRecord;)V";
    }
    else if (strcmp(methodName, "addRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "setRejections") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "addRejection") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRejection;)V";
    }
    else if (strcmp(methodName, "addRejections") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "getRecords") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRejections") == 0)
    {
        return "()Ljava/util/List;";
    }
    return NULL;
}

const char *MessageApiEndpoint::getProtocolRecordMethodSignature(const char* methodName)
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

const char *MessageApiEndpoint::getRecordMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "isValid") == 0)
    {
        return "()Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getCopy") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "getFieldIds") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "hasField") == 0)
    {
        return "(Ljava/lang/String;)Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getFields") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getField") == 0)
    {
        return "(Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/IField;";
    }
    else if (strcmp(methodName, "getConditionIds") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "hasCondition") == 0)
    {
        return "(Ljava/lang/String;)Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getConditions") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getCondition") == 0)
    {
        return "(Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/ICondition;";
    }
    return NULL;
}

const char *MessageApiEndpoint::getRejectionMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getCopy") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRejection;";
    }
    else if (strcmp(methodName, "getReasons") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "addReason") == 0)
    {
        return "(Ljava/lang/String;)V";
    }

    return NULL;
}

const char *MessageApiEndpoint::getFieldMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getId") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getType") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getValue") == 0)
    {
        return "()Ljava/lang/Object;";
    }
    else if (strcmp(methodName, "isValid") == 0)
    {
        return "()Z";
    }
    else if (strcmp(methodName, "isRequired") == 0)
    {
        return "()Z";
    }
    else if (strcmp(methodName, "setValue") == 0)
    {
        return "(Ljava/lang/Object;)V";
    }
    return NULL;
}

const char * MessageApiEndpoint::getConditionMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getId") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getType") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getOperator") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getValue") == 0)
    {
        return "()Ljava/lang/Object;";
    }
    else if (strcmp(methodName, "setValue") == 0)
    {
        return "(Ljava/lang/Object;)V";
    }

    return NULL;
}

struct record *MessageApiEndpoint::getStateContainer()
{
    jobject jstatecontainer = this->jvm->CallObjectMethod(this->endpoint, this->getStateContainerMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jstatecontainer));
    record->jrecord = jstatecontainer;
    return record;
}

struct field_list *MessageApiEndpoint::getDefaultFields()
{
    jobject jFieldList = this->jvm->CallObjectMethod(this->endpoint, this->getDefaultFieldsMethodId);

    int fieldCount = this->getJListLength(jFieldList);
    struct field **fields = (struct field **)malloc(sizeof(struct field *) * fieldCount);

    for (int i = 0; i < fieldCount; i++)
    {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->getJListItemMethodId, i));
        struct field *field = (struct field *)malloc(sizeof(field) + sizeof(jfield));
        field->jfield = (jobject)jfield;
        fields[i] = field;
    }

    struct field_list *field_list = (struct field_list *)malloc(sizeof(struct field_list) + sizeof(fields));
    field_list->count = fieldCount;
    field_list->fields = fields;
    return field_list;
}

struct packet *MessageApiEndpoint::createPacket()
{
    jobject jpacket = this->jvm->CallObjectMethod(this->endpoint, this->createPacketMethodId);
    struct packet *packet = (struct packet *)malloc(sizeof(struct packet) + sizeof(jpacket));
    packet->jpacket = jpacket;
    return packet;
}

struct record *MessageApiEndpoint::createRecord()
{
    jobject jrecord = this->jvm->CallObjectMethod(this->endpoint, this->createRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

struct rejection *MessageApiEndpoint::createRejection(struct record *record, const char *reason)
{
    jstring jreason = this->toJavaString(reason);
    jobject jrejection = this->jvm->CallObjectMethod(this->endpoint, this->createRejectionMethodId, record->jrecord, jreason);
    struct rejection *rejection = (struct rejection *)malloc(sizeof(struct rejection) + sizeof(jrejection));
    rejection->jrejection = jrejection;
    this->jvm->DeleteLocalRef(jreason);
    return rejection;
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
jobject MessageApiEndpoint::getProtocolRecords(const char* method, const char* key, const char* val)
{
    if (strcmp(method, "getRecords") == 0)
    {
        return this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsMethodId);
    }
    else if (strcmp(method, "getRecordsByCollection") == 0)
    {
        jstring javaKey = this->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByCollectionMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByTransformation") == 0)
    {
        jstring javaKey = this->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByTransformationMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByUUID") == 0)
    {
        jstring javaKey = this->toJavaString(key);
        jobject protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByUUIDMethodId, javaKey);
        this->jvm->DeleteLocalRef(javaKey);
        return protocolRecords;
    }
    else if (strcmp(method, "getRecordsByClassifier") == 0)
    {
        jstring javaKey = this->toJavaString(key);
        jstring javaVal = this->toJavaString(val);
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

struct record_list * MessageApiEndpoint::getRecords(const char *recordMethod, const char *key, const char *val)
{
    jobject jprotocolRecords = this->getProtocolRecords(recordMethod, key, val);
    int recordCount = this->getJListLength(jprotocolRecords);
    struct record_list *record_list = (struct record_list *) malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jprotocolRecords;

    return record_list;
}

struct record *MessageApiEndpoint::getRecord(struct record_list *record_list, int index)
{
    jobject jrecord = this->jvm->CallObjectMethod(record_list->jrecords, this->getJListItemMethodId, index);
    struct record *record = (struct record *) malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

void MessageApiEndpoint::setPacketRecords(struct packet *packet, struct record_list *records)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->setPacketRecordsMethodId, records->jrecords);
}

void MessageApiEndpoint::addPacketRecord(struct packet *packet, struct record *record)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addPacketRecordMethodId, record->jrecord);
}

void MessageApiEndpoint::addPacketRecords(struct packet *packet, struct record_list *records)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addPacketRecordsMethodId, records->jrecords);
}

void MessageApiEndpoint::setPacketRejections(struct packet *packet, struct rejection_list *rejections)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->setPacketRejectionsMethodId, rejections->jrejections);
}

void MessageApiEndpoint::addPacketRejection(struct packet *packet, struct rejection *rejection)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addPacketRejectionMethodId, rejection->jrejection);
}

void MessageApiEndpoint::addPacketRejections(struct packet *packet, struct rejection_list *rejections)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addPacketRejectionsMethodId, rejections->jrejections);
}

struct record_list *MessageApiEndpoint::getPacketRecords(struct packet *packet)
{
    jobject jPacketRecords = this->jvm->CallObjectMethod(packet->jpacket, this->getPacketRecordsMethodId);
    int recordCount = this->getJListLength(jPacketRecords);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jPacketRecords;

    return record_list;
}

struct rejection_list *MessageApiEndpoint::getPacketRejections(struct packet *packet)
{
    jobject jPacketRejections = this->jvm->CallObjectMethod(packet->jpacket, this->getPacketRejectionsMethodId);
    int rejectionCount = this->getJListLength(jPacketRejections);
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = rejectionCount;
    rejection_list->jrejections = jPacketRejections;

    return rejection_list;
}

int MessageApiEndpoint::getJListLength(jobject jList)
{
    return (int)this->jvm->CallIntMethod(jList, this->getJListSizeMethodId);
}

struct string_list *MessageApiEndpoint::translateFromJavaStringList(jobject jList)
{
    int stringCount = this->getJListLength(jList);
    char **strings = (char **)malloc(sizeof(char *) * stringCount);
    int maxStringLength = 0;
    for (int i = 0; i < stringCount; i++) {
        jstring jString = static_cast<jstring>(this->jvm->CallObjectMethod(jList, this->getJListItemMethodId, i));
        const char *tempString = this->jvm->GetStringUTFChars(jString, NULL);
        int tempMaxStringLength = strlen(tempString);
        if (tempMaxStringLength > maxStringLength) {
            maxStringLength = tempMaxStringLength;
        }
        strings[i] = (char*) malloc((tempMaxStringLength+1) * sizeof(char));
        strcpy(strings[i], tempString);
        this->jvm->ReleaseStringUTFChars(jString, tempString);
        this->jvm->DeleteLocalRef(jString);
    }

    struct string_list *string_list = (struct string_list*) malloc(sizeof(struct string_list) + sizeof(strings));
    string_list->count = stringCount;
    string_list->max_length = maxStringLength;
    string_list->strings = strings;
    return string_list;
}

bool MessageApiEndpoint::getRecordIsValid(struct record *record)
{
    return (bool)this->jvm->CallBooleanMethod(record->jrecord, this->getRecordIsValidMethodId);
}

struct record *MessageApiEndpoint::getRecordCopy(struct record *record)
{
    jobject jRecordCopy = this->jvm->CallObjectMethod(record->jrecord, this->getRecordCopyMethodId);
    struct record *recordCopy = (struct record *)malloc(sizeof(struct record) + sizeof(jRecordCopy));
    recordCopy->jrecord = jRecordCopy;
    return recordCopy;
}

bool MessageApiEndpoint::getRecordHasField(struct record *record, const char *fieldId)
{
    jstring jFieldId = this->toJavaString(fieldId);
    bool hasJField = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->getRecordHasFieldMethodId, jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return hasJField;
}
struct string_list *MessageApiEndpoint::getFieldIds(struct record *record)
{
    jobject jFieldIdList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldIdsMethodId);
    struct string_list *field_ids = this->translateFromJavaStringList(jFieldIdList);
    this->jvm->DeleteLocalRef(jFieldIdList);
    return field_ids;
}
struct field_list *MessageApiEndpoint::getFields(struct record *record)
{
    jobject jFieldList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldsMethodId);

    int fieldCount = this->getJListLength(jFieldList);
    struct field **fields = (struct field **)malloc(sizeof(struct field *) * fieldCount);

    for (int i = 0; i < fieldCount; i++)
    {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->getJListItemMethodId, i));
        struct field *field = (struct field *)malloc(sizeof(field) + sizeof(jfield));
        field->jfield = (jobject)jfield;
        fields[i] = field;
    }

    struct field_list *field_list = (struct field_list *)malloc(sizeof(struct field_list) + sizeof(fields));
    field_list->count = fieldCount;
    field_list->fields = fields;
    return field_list;
}

struct field *MessageApiEndpoint::getField(struct record *record, const char *fieldId)
{
    jstring jFieldId = this->toJavaString(fieldId);
    jobject jField = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(struct field) + sizeof(jField));
    field->jfield = jField;
    this->jvm->DeleteLocalRef(jFieldId);
    return field;
}

bool MessageApiEndpoint::getRecordHasCondition(struct record *record, const char *conditionId)
{
    jstring jConditionId = this->toJavaString(conditionId);
    bool hasJCondition = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->getRecordHasConditionMethodId, jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return hasJCondition;
}

struct string_list *MessageApiEndpoint::getConditionIds(struct record *record)
{
    jobject jConditionIdList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionIdsMethodId);
    struct string_list *condition_ids = this->translateFromJavaStringList(jConditionIdList);
    this->jvm->DeleteLocalRef(jConditionIdList);
    return condition_ids;
}

struct condition_list *MessageApiEndpoint::getConditions(struct record *record)
{
    jobject jConditionList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionsMethodId);

    int conditionCount = this->getJListLength(jConditionList);
    struct condition **conditions = (struct condition **)malloc(sizeof(struct condition *) * conditionCount);

    for (int i = 0; i < conditionCount; i++)
    {
        jobject jcondition = static_cast<jobject>(this->jvm->CallObjectMethod(jConditionList, this->getJListItemMethodId, i));
        struct condition *condition = (struct condition *)malloc(sizeof(condition) + sizeof(jcondition));
        condition->jcondition = (jobject)jcondition;
        conditions[i] = condition;
    }

    struct condition_list *condition_list = (struct condition_list *)malloc(sizeof(struct condition_list) + sizeof(conditions));
    condition_list->count = conditionCount;
    condition_list->conditions = conditions;
    return condition_list;
}

struct condition *MessageApiEndpoint::getCondition(struct record *record, const char *conditionId)
{
    jstring jConditionId = this->toJavaString(conditionId);
    jobject jCondition = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionMethodId, jConditionId);
    struct condition *condition = (struct condition *)malloc(sizeof(struct condition) + sizeof(jCondition));
    condition->jcondition = jCondition;
    this->jvm->DeleteLocalRef(jConditionId);
    return condition;
}

const char *MessageApiEndpoint::getFieldId(struct field *field)
{
    jstring jFieldId = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getFieldIdMethodId));
    const char *fieldId = this->fromJavaString(jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return fieldId;
}

const char *MessageApiEndpoint::getFieldType(struct field *field)
{
    jstring jFieldType = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getFieldTypeMethodId));
    const char *fieldType = this->fromJavaString(jFieldType);
    this->jvm->DeleteLocalRef(jFieldType);
    return fieldType;
}

bool MessageApiEndpoint::getFieldIsValid(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->getFieldIsValidMethodId);
}

bool MessageApiEndpoint::getFieldIsRequired(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->getFieldIsRequiredMethodId);
}

bool MessageApiEndpoint::getFieldIsNull(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    if (value->jvalue == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct val *MessageApiEndpoint::getFieldVal(struct field *field)
{
    jobject jFieldValue = this->jvm->CallObjectMethod(field->jfield, this->getFieldValueMethodId);
    struct val *value = (struct val *)malloc(sizeof(value) + sizeof(jFieldValue));
    value->jvalue = jFieldValue;
    return value;
}

int MessageApiEndpoint::getFieldIntVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->getJIntMethodId);
    return intVal;
}

long MessageApiEndpoint::getFieldLongVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->getJLongMethodId);
    return longVal;
}

float MessageApiEndpoint::getFieldFloatVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->getJFloatMethodId);
    return floatVal;
}

double MessageApiEndpoint::getFieldDoubleVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->getJDoubleMethodId);
    return doubleVal;
}

signed char MessageApiEndpoint::getFieldByteVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->getJByteMethodId);
    return (signed char)jByte;
}

const char *MessageApiEndpoint::getFieldStringVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool MessageApiEndpoint::getFieldBoolVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->getJBoolMethodId);
    return boolVal;
}

short MessageApiEndpoint::getFieldShortVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->getJShortMethodId);
    return shortVal;
}

struct val_list *MessageApiEndpoint::getFieldListVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    int entryCount = this->getJListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = entryCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

void MessageApiEndpoint::setFieldVal(struct field *field, struct val *value)
{
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, value->jvalue);
}

void MessageApiEndpoint::setFieldIntVal(struct field *field, int value)
{
    jobject jIntVal = jvm->NewObject(this->jIntClass, this->createJIntMethodId, (jint)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void MessageApiEndpoint::setFieldLongVal(struct field *field, long value)
{
    jobject jLongVal = jvm->NewObject(this->jLongClass, this->createJLongMethodId, (jlong)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void MessageApiEndpoint::setFieldFloatVal(struct field *field, float value)
{
    jobject jFloatVal = jvm->NewObject(this->jFloatClass, this->createJFloatMethodId, (jfloat)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void MessageApiEndpoint::setFieldDoubleVal(struct field *field, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->jDoubleClass, this->createJDoubleMethodId, (jdouble)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void MessageApiEndpoint::setFieldByteVal(struct field *field, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->jByteClass, this->createJByteMethodId, (jbyte)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void MessageApiEndpoint::setFieldStringVal(struct field *field, const char *value)
{
    jstring jStringVal = this->toJavaString(value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void MessageApiEndpoint::setFieldBoolVal(struct field *field, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->jBoolClass, this->createJBoolMethodId, (jboolean)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void MessageApiEndpoint::setFieldShortVal(struct field *field, short value)
{
    jobject jShortVal = jvm->NewObject(this->jShortClass, this->createJShortMethodId, (jshort)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jShortVal);
    this->jvm->DeleteLocalRef(jShortVal);
}

void MessageApiEndpoint::setFieldListVal(struct field *field, struct val_list *value)
{
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, value->jlist);
}

const char *MessageApiEndpoint::getConditionId(struct condition *condition)
{
    jstring jConditionId = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getConditionIdMethodId));
    const char *conditionId = this->fromJavaString(jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return conditionId;
}

const char *MessageApiEndpoint::getConditionType(struct condition *condition)
{
    jstring jConditionType = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getConditionTypeMethodId));
    const char *conditionType = this->fromJavaString(jConditionType);
    this->jvm->DeleteLocalRef(jConditionType);
    return conditionType;
}

const char *MessageApiEndpoint::getConditionOperator(struct condition *condition)
{
    jstring jConditionOperator = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getConditionOperatorMethodId));
    const char *conditionOperator = this->fromJavaString(jConditionOperator);
    this->jvm->DeleteLocalRef(jConditionOperator);
    return conditionOperator;
}

bool MessageApiEndpoint::getConditionIsNull(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    if (value->jvalue == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
struct val *MessageApiEndpoint::getConditionVal(struct condition *condition)
{
    jobject jConditionValue = this->jvm->CallObjectMethod(condition->jcondition, this->getConditionValueMethodId);
    struct val *value = (struct val *)malloc(sizeof(value) + sizeof(jConditionValue));
    value->jvalue = jConditionValue;
    return value;
}

int MessageApiEndpoint::getConditionIntVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->getJIntMethodId);
    return intVal;
}

long MessageApiEndpoint::getConditionLongVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->getJLongMethodId);
    return longVal;
}

float MessageApiEndpoint::getConditionFloatVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->getJFloatMethodId);
    return floatVal;
}

double MessageApiEndpoint::getConditionDoubleVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->getJDoubleMethodId);
    return doubleVal;
}

signed char MessageApiEndpoint::getConditionByteVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->getJByteMethodId);
    return (signed char)jByte;
}

const char *MessageApiEndpoint::getConditionStringVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool MessageApiEndpoint::getConditionBoolVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->getJBoolMethodId);
    return boolVal;
}

short MessageApiEndpoint::getConditionShortVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->getJShortMethodId);
    return shortVal;
}

struct val_list *MessageApiEndpoint::getConditionListVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    int entryCount = this->getJListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = entryCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

jobject MessageApiEndpoint::getObjectEntry(struct val_list *val_list, int index)
{
    return static_cast<jobject>(this->jvm->CallObjectMethod(val_list->jlist, this->getJListItemMethodId, index));
}

struct list_entry *MessageApiEndpoint::getEntry(struct val_list *list, int index)
{
    struct list_entry *listEntry = (struct list_entry *)malloc(sizeof(struct list_entry));
    listEntry->jentry = this->getObjectEntry(list, index);
    return listEntry;
}

struct val_list *MessageApiEndpoint::getListEntry(struct val_list *list, int index)
{
    jobject listEntry = this->getObjectEntry(list, index);
    int entryCount = this->getJListLength(listEntry);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = entryCount;
    valueList->jlist = listEntry;
    return valueList;
}

int MessageApiEndpoint::getIntEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    int val = (int)this->jvm->CallIntMethod(list_entry, this->getJIntMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

long MessageApiEndpoint::getLongEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    long val = (long)this->jvm->CallLongMethod(list_entry, this->getJLongMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

float MessageApiEndpoint::getFloatEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    float val = (float)this->jvm->CallFloatMethod(list_entry, this->getJFloatMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

double MessageApiEndpoint::getDoubleEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    double val = (double)this->jvm->CallDoubleMethod(list_entry, this->getJDoubleMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

signed char MessageApiEndpoint::getByteEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    signed char val = (signed char)this->jvm->CallByteMethod(list_entry, this->getJByteMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

const char *MessageApiEndpoint::getStringEntry(struct val_list *list, int index)
{
    jstring jString = static_cast<jstring>(this->jvm->CallObjectMethod(list->jlist, this->getJListItemMethodId, index));
    const char *val = this->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return val;
}

bool MessageApiEndpoint::getBoolEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    bool val = (bool)this->jvm->CallBooleanMethod(list_entry, this->getJBoolMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

short MessageApiEndpoint::getShortEntry(struct val_list *list, int index)
{
    jobject list_entry = this->getObjectEntry(list, index);
    short val = (short)this->jvm->CallShortMethod(list_entry, this->getJShortMethodId);
    jvm->DeleteLocalRef(list_entry);
    return val;
}

void MessageApiEndpoint::setConditionVal(struct condition *condition, struct val *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, value->jvalue);
}

void MessageApiEndpoint::setConditionIntVal(struct condition *condition, int value)
{
    jobject jIntVal = jvm->NewObject(this->jIntClass, this->createJIntMethodId, (jint)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void MessageApiEndpoint::setConditionLongVal(struct condition *condition, long value)
{
    jobject jLongVal = jvm->NewObject(this->jLongClass, this->createJLongMethodId, (jlong)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void MessageApiEndpoint::setConditionFloatVal(struct condition *condition, float value)
{
    jobject jFloatVal = jvm->NewObject(this->jFloatClass, this->createJFloatMethodId, (jfloat)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void MessageApiEndpoint::setConditionDoubleVal(struct condition *condition, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->jDoubleClass, this->createJDoubleMethodId, (jdouble)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void MessageApiEndpoint::setConditionByteVal(struct condition *condition, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->jByteClass, this->createJByteMethodId, (jbyte)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void MessageApiEndpoint::setConditionStringVal(struct condition *condition, const char *value)
{
    jstring jStringVal = this->toJavaString(value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void MessageApiEndpoint::setConditionBoolVal(struct condition *condition, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->jBoolClass, this->createJBoolMethodId, (jboolean)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void MessageApiEndpoint::setConditionShortVal(struct condition *condition, short value)
{
    jobject jShortVal = jvm->NewObject(this->jBoolClass, this->createJShortMethodId, (jshort)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jShortVal);
    this->jvm->DeleteLocalRef(jShortVal);
}

void MessageApiEndpoint::setConditionListVal(struct condition *condition, struct val_list *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, value->jlist);
}

struct record_list *MessageApiEndpoint::createRecordList()
{
    jobject jList = this->jvm->NewObject(this->jArrayListClass, this->createJArrayListMethodId);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = 0;
    record_list->jrecords = jList;
    return record_list;
}

void MessageApiEndpoint::addRecordEntry(struct record_list *record_list, struct record *record)
{
    this->jvm->CallVoidMethod(record_list->jrecords, this->addJListItemMethodId, record->jrecord);
    record_list->count += 1;
}

struct rejection_list *MessageApiEndpoint::createRejectionList()
{
    jobject jList = this->jvm->NewObject(this->jArrayListClass, this->createJArrayListMethodId);
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = 0;
    rejection_list->jrejections = jList;
    return rejection_list;
}

void MessageApiEndpoint::addRejectionEntry(struct rejection_list *rejection_list, struct rejection *rejection)
{
    this->jvm->CallVoidMethod(rejection_list->jrejections, this->addJListItemMethodId, rejection->jrejection);
    rejection_list->count += 1;
}

struct rejection *MessageApiEndpoint::getRejectionCopy(struct rejection *rejection)
{
    jobject jRejectionCopy = this->jvm->CallObjectMethod(rejection->jrejection, this->getRejectionCopyMethodId);
    struct rejection *rejectionCopy = (struct rejection *)malloc(sizeof(struct rejection) + sizeof(jRejectionCopy));
    rejectionCopy->jrejection = jRejectionCopy;
    return rejectionCopy;
}

struct record *MessageApiEndpoint::getRejectionRecord(struct rejection *rejection)
{
    jobject jRecord = this->jvm->CallObjectMethod(rejection->jrejection, this->getRejectionRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jRecord));
    record->jrecord = jRecord;
    return record;
}

struct string_list *MessageApiEndpoint::getRejectionReasons(struct rejection *rejection)
{
    jobject jReasons = this->jvm->CallObjectMethod(rejection->jrejection, this->getRejectionReasonsMethodId);
    struct string_list *reasons = this->translateFromJavaStringList(jReasons);
    return reasons;
}

void MessageApiEndpoint::addRejectionReason(struct rejection *rejection, const char *reason)
{
    jstring jReason = this->toJavaString(reason);
    this->jvm->CallVoidMethod(rejection->jrejection, this->addRejectionReasonMethodId, jReason);
}

struct val_list *MessageApiEndpoint::createList()
{
    jobject jList = this->jvm->NewObject(this->jArrayListClass, this->createJArrayListMethodId);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = 0;
    valueList->jlist = jList;
    return valueList;
}

void MessageApiEndpoint::addObjectEntry(struct val_list *list, jobject val)
{
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, val);
    list->count += 1;
}

void MessageApiEndpoint::addEntry(struct val_list *list, struct list_entry *entry)
{
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, entry->jentry);
    list->count += 1;
}

void MessageApiEndpoint::addIntEntry(struct val_list *list, int val)
{
    jobject jVal = jvm->NewObject(this->jIntClass, this->createJIntMethodId, (jint)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addLongEntry(struct val_list *list, long val)
{
    jobject jVal = jvm->NewObject(this->jLongClass, this->createJLongMethodId, (jlong)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addFloatEntry(struct val_list *list, float val)
{
    jobject jVal = jvm->NewObject(this->jFloatClass, this->createJFloatMethodId, (jfloat)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addDoubleEntry(struct val_list *list, double val)
{
    jobject jVal = jvm->NewObject(this->jDoubleClass, this->createJDoubleMethodId, (jdouble)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addByteEntry(struct val_list *list, signed char val)
{
    jobject jVal = jvm->NewObject(this->jByteClass, this->createJByteMethodId, (jbyte)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addStringEntry(struct val_list *list, const char *val)
{
    jstring jVal = this->toJavaString(val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addBoolEntry(struct val_list *list, bool val)
{
    jobject jVal = jvm->NewObject(this->jBoolClass, this->createJBoolMethodId, (jboolean)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addShortEntry(struct val_list *list, short val)
{
    jobject jVal = jvm->NewObject(this->jShortClass, this->createJShortMethodId, (jshort)val);
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void MessageApiEndpoint::addListEntry(struct val_list *list, struct val_list *val)
{
    this->jvm->CallVoidMethod(list->jlist, this->addJListItemMethodId, val->jlist);
    list->count += 1;
}
