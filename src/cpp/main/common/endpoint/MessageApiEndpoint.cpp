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

    this->loadRecordRefs();
    this->loadGlobalTypeRefs();
    this->loadTypeMethodIds();
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        this->jvm->DeleteGlobalRef(this->endpoint);
        this->jvm->DeleteGlobalRef(this->protocolRecord);
        this->jvm->DeleteGlobalRef(this->jException);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void MessageApiEndpoint::loadRecordRefs()
{

    jclass protocolRecordClass = this->getObjectClass(this->protocolRecord);

    this->getRecordsMethodId = this->getMethod(protocolRecordClass, "getRecords", this->getRecordMethodSignature("getRecords"), false);
    this->getRecordsByCollectionMethodId = this->getMethod(protocolRecordClass, "getRecordsByCollection", this->getRecordMethodSignature("getRecordsByCollection"), false);
    this->getRecordsByUUIDMethodId = this->getMethod(protocolRecordClass, "getRecordsByUUID", this->getRecordMethodSignature("getRecordsByUUID"), false);
    this->getRecordsByTransformationMethodId = this->getMethod(protocolRecordClass, "getRecordsByTransformation", this->getRecordMethodSignature("getRecordsByTransformation"), false);
    this->getRecordsByClassifierMethodId = this->getMethod(protocolRecordClass, "getRecordsByClassifier", this->getRecordMethodSignature("getRecordsByClassifier"), false);

    this->jvm->DeleteLocalRef(protocolRecordClass);
}

void MessageApiEndpoint::loadGlobalTypeRefs()
{
    
}

/**
 * Loads the default value types for MessageApiEndpoint.
 * Default types are relatively primitive data types. More complicated 'struct' types
 * will require extension of this by user methods.
 * TODO: A mechanism for allowing extension will eventually be provided.
 * The included default types have associated access,modification,and release methods.
 * Each also has an associated 'list' method (i.e., string has string_list, byte has byte_list, etc.)
 * Default types include the following:
 * integer, long, float, double, string, byte, boolean
 */
void MessageApiEndpoint::loadTypeMethodIds()
{
    jclass jListClass = static_cast<jclass>(this->jvm->NewLocalRef(this->jvm->FindClass("java/util/List")));
    this->getJListSizeMethodId = this->jvm->GetMethodID(jListClass, "size", "()I");
    this->getJListItemMethodId = this->jvm->GetMethodID(jListClass, "get", "(I)Ljava/lang/Object;");
    this->jvm->DeleteLocalRef(jListClass);

    jclass jBoolClass = this->getNamedClass("java/lang/Boolean");
    this->getJBoolMethodId = this->jvm->GetMethodID(jBoolClass, "booleanValue", "()Z");
    this->makeJBoolMethodId = this->jvm->GetMethodID(jBoolClass, "<init>", "(Z)V");
    this->jvm->DeleteLocalRef(jBoolClass);

    jclass jByteClass = this->getNamedClass("java/lang/Byte");
    this->getJByteMethodId = this->jvm->GetMethodID(jByteClass, "byteValue", "()B");
    this->makeJByteMethodId = this->jvm->GetMethodID(jByteClass, "<init>", "(B)V");
    this->jvm->DeleteLocalRef(jByteClass);

    jclass jIntClass = this->getNamedClass("java/lang/Integer");
    this->getJIntMethodId = this->jvm->GetMethodID(jIntClass, "intValue", "()I");
    this->makeJIntMethodId = this->jvm->GetMethodID(jIntClass, "<init>", "(I)V");
    this->jvm->DeleteLocalRef(jIntClass);

    jclass jLongClass = this->getNamedClass("java/lang/Long");
    this->getJLongMethodId = this->jvm->GetMethodID(jLongClass, "longValue", "()J");
    this->makeJLongMethodId = this->jvm->GetMethodID(jLongClass, "<init>", "(J)V");
    this->jvm->DeleteLocalRef(jLongClass);

    jclass jFloatClass = this->getNamedClass("java/lang/Float");
    this->getJFloatMethodId = this->jvm->GetMethodID(jFloatClass, "floatValue", "()F");
    this->makeJFloatMethodId = this->jvm->GetMethodID(jFloatClass, "<init>", "(F)V");
    this->jvm->DeleteLocalRef(jFloatClass);

    jclass jDoubleClass = this->getNamedClass("java/lang/Double");
    this->getJDoubleMethodId = this->jvm->GetMethodID(jDoubleClass, "doubleValue", "()D");
    this->makeJDoubleMethodId = this->jvm->GetMethodID(jDoubleClass, "<init>", "(D)V");
    this->jvm->DeleteLocalRef(jDoubleClass);

}

/**
 * Default error handling for the MessageApiEndpoint Class.
 */
void MessageApiEndpoint::checkAndThrow(const char *errorMessage)
{
    if (this->jvm->ExceptionCheck())
    {
        std::cout << "MessageApiEndpoint.cpp errored with the following message:" << errorMessage << std::endl;
        this->jvm->ThrowNew(this->jException, errorMessage);
    }
}


jclass MessageApiEndpoint::getNamedClass(const char *className)
{
    jclass clazz = this->jvm->FindClass(className);
    const char *msg = "getNamedClass> failed.";
    checkAndThrow(msg);
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
    checkAndThrow(msg);
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
jobject MessageApiEndpoint::getProtocolRecords(const char* method, const char* key, const char* val)
{
    if (method == "getRecords")
    {
        return this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsMethodId);
    }
    jstring javaKey = toJavaString(key);
    jobject protocolRecords;
    if (method == "getRecordsByCollection")
    {
        protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByCollectionMethodId, javaKey);
    }
    else if (method == "getRecordsByTransformation")
    {
        protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByTransformationMethodId, javaKey);
    }
    else if (method == "getRecordsByUUID")
    {
        protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByUUIDMethodId, javaKey);
    }
    else if (method == "getRecordsByClassifier")
    {
        jstring javaVal = toJavaString(val);
        protocolRecords = this->jvm->CallObjectMethod(this->protocolRecord, this->getRecordsByClassifierMethodId, javaKey, javaVal);
        this->jvm->DeleteLocalRef(javaVal);
    }
    this->jvm->DeleteLocalRef(javaKey);
    return protocolRecords;
}

struct record_list * MessageApiEndpoint::getRecords(const char *recordMethod, const char *key, const char *val)
{
    jobject jprotocolRecords = this->getProtocolRecords(recordMethod, key, val);

    int recordCount = this->jvm->CallIntMethod(jprotocolRecords, this->getJListSizeMethodId);
    struct record_list *record_list = (struct record_list *) malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jprotocolRecords;

    return record_list;
}

struct record * MessageApiEndpoint::getRecord(struct record_list * record_list, int index)
{
    jobject jRecordRef = this->jvm->NewLocalRef(record_list->jrecords);

    jobject jrecord = static_cast<jobject>(this->jvm->CallObjectMethod(jRecordRef, this->getJListItemMethodId, index));
    struct record *record = (struct record *) malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;

    this->jvm->DeleteLocalRef(jRecordRef);

    return record;
}

struct string_list * MessageApiEndpoint::getFieldIds(struct record *record) {
    const char *methodName = "getFieldIds";

    jobject jRecordRef = this->jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldIdMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);
    jobject jFieldIdList = this->jvm->CallObjectMethod(jRecordRef, jFieldIdMethodId);

    int fieldCount = this->jvm->CallIntMethod(jFieldIdList, this->getJListSizeMethodId);
    char **fieldIds = (char**) malloc(sizeof(char*) * fieldCount);

    int maxFieldIdLength = 0;
    for (int i = 0; i < fieldCount; i++) {
        jstring fieldId = static_cast<jstring>(this->jvm->CallObjectMethod(jFieldIdList, this->getJListItemMethodId, i));
        const char *tempFieldId = this->jvm->GetStringUTFChars(fieldId, NULL);
        int tempMaxFieldIdLength = strlen(tempFieldId);
        if (tempMaxFieldIdLength > maxFieldIdLength) {
            maxFieldIdLength = tempMaxFieldIdLength;
        }
        fieldIds[i] = (char*) malloc((tempMaxFieldIdLength+1) * sizeof(char));
        strcpy(fieldIds[i], tempFieldId);
        this->jvm->ReleaseStringUTFChars(fieldId, tempFieldId);
        this->jvm->DeleteLocalRef(fieldId);
    }

    struct string_list *field_names = (struct string_list*) malloc(sizeof(struct string_list) + sizeof(fieldIds));
    field_names->max_length = maxFieldIdLength;
    field_names->count = fieldCount;
    field_names->strings = fieldIds;

    this->jvm->DeleteLocalRef(jFieldIdList);
    this->jvm->DeleteLocalRef(jRecordClass);
    this->jvm->DeleteLocalRef(jRecordRef);

    return field_names;
}

struct field_list * MessageApiEndpoint::getFields(struct record *record) {
    const char * methodName = "getFields";

    jobject jRecordRef = this->jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jobject jFieldList = this->jvm->CallObjectMethod(jRecordRef, jFieldMethodId);

    int fieldCount = this->jvm->CallIntMethod(jFieldList, this->getJListSizeMethodId);
    struct field **fields = (struct field**)malloc(sizeof(struct field*) * fieldCount);

    for (int i = 0; i < fieldCount; i++) {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->getJListItemMethodId, i));
        struct field *field = (struct field*)malloc(sizeof(field) + sizeof(jfield));
        field->jfield = (jobject)jfield;
        fields[i] = field;
    }

    struct field_list *field_list = (struct field_list*)malloc(sizeof(struct field_list) + sizeof(fields));
    field_list->count = fieldCount;
    field_list->fields = fields;

    this->jvm->DeleteLocalRef(jRecordClass);
    this->jvm->DeleteLocalRef(jRecordRef);

    return field_list;

}

struct field * MessageApiEndpoint::getField(struct record *record, const char* fieldId) {
    const char * methodName = "getField";

    jobject jRecordRef = this->jvm->NewLocalRef(record->jrecord);
    jclass jRecordClass = getObjectClass(jRecordRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldId = toJavaString(fieldId);
    jobject jField = this->jvm->CallObjectMethod(jRecordRef, jFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(field) + sizeof(jField));
    field->jfield = jField;

    this->jvm->DeleteLocalRef(jFieldId);
    this->jvm->DeleteLocalRef(jRecordClass);
    this->jvm->DeleteLocalRef(jRecordRef);

    return field;
}

const char * MessageApiEndpoint::getFieldId(struct field *field) {
    const char * methodName = "getId";

    jobject jFieldRef = this->jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldId = static_cast<jstring>(this->jvm->CallObjectMethod(jFieldRef, jFieldMethodId));
    const char * fieldId = this->fromJavaString(jFieldId);

    this->jvm->DeleteLocalRef(jFieldId);
    this->jvm->DeleteLocalRef(jFieldRef);

    return fieldId;
}

const char * MessageApiEndpoint::getFieldType(struct field *field)
{
    const char * methodName = "getType";

    jobject jFieldRef = this->jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jstring jFieldType = static_cast<jstring>(this->jvm->CallObjectMethod(jFieldRef, jFieldMethodId));
    const char *fieldType = this->fromJavaString(jFieldType);

    this->jvm->DeleteLocalRef(jFieldType);
    this->jvm->DeleteLocalRef(jRecordClass);
    this->jvm->DeleteLocalRef(jFieldRef);

    return fieldType;
}

struct field_value *MessageApiEndpoint::getFieldValue(struct field *field)
{
    const char * methodName = "getValue";

    jobject jFieldRef = this->jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    jobject jFieldValue = this->jvm->CallObjectMethod(jFieldRef, jFieldMethodId);

    struct field_value *field_value = (struct field_value *)malloc(sizeof(field_value) + sizeof(jFieldValue));
    field_value->jvalue = jFieldValue;

    this->jvm->DeleteLocalRef(jRecordClass);
    this->jvm->DeleteLocalRef(jFieldRef);

    return field_value;
}

int MessageApiEndpoint::fieldValueAsInteger(struct field_value *field_value)
{
    jobject jFieldRef = this->jvm->NewLocalRef(field_value->jvalue);

    //jint jIntFieldRef = reinterpret_cast<jint>(jFieldRef);

    //int intFieldValue = (int) jIntFieldRef;

    this->jvm->DeleteLocalRef(jFieldRef);

    return 1;
}

bool MessageApiEndpoint::getFieldIsValid(struct field *field)
{
    const char *methodName = "isValid";

    jobject jFieldRef = this->jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    this->jvm->DeleteLocalRef(jFieldRef);
}

bool MessageApiEndpoint::getFieldIsRequired(struct field *field)
{
    const char *methodName = "isRequired";

    jobject jFieldRef = this->jvm->NewLocalRef(field->jfield);
    jclass jRecordClass = getObjectClass(jFieldRef);
    jmethodID jFieldMethodId = getMethod(jRecordClass, methodName, getFieldMethodSignature(methodName), false);

    this->jvm->DeleteLocalRef(jFieldRef);
}
