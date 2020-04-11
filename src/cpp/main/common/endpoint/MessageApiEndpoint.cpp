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

    this->loadProtocolRecordMethodIds();
    this->loadRecordMethodIds();
    this->loadFieldMethodIds();
    this->loadValueTypeMethodIds();
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

void MessageApiEndpoint::loadProtocolRecordMethodIds()
{

    jclass protocolRecordClass = this->getObjectClass(this->protocolRecord);

    this->getRecordsMethodId = this->getMethod(protocolRecordClass, "getRecords", this->getRecordMethodSignature("getRecords"), false);
    this->getRecordsByCollectionMethodId = this->getMethod(protocolRecordClass, "getRecordsByCollection", this->getRecordMethodSignature("getRecordsByCollection"), false);
    this->getRecordsByUUIDMethodId = this->getMethod(protocolRecordClass, "getRecordsByUUID", this->getRecordMethodSignature("getRecordsByUUID"), false);
    this->getRecordsByTransformationMethodId = this->getMethod(protocolRecordClass, "getRecordsByTransformation", this->getRecordMethodSignature("getRecordsByTransformation"), false);
    this->getRecordsByClassifierMethodId = this->getMethod(protocolRecordClass, "getRecordsByClassifier", this->getRecordMethodSignature("getRecordsByClassifier"), false);

    this->jvm->DeleteLocalRef(protocolRecordClass);
}

void MessageApiEndpoint::loadRecordMethodIds()
{
    jclass recordClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IRecord");
    this->getRecordFieldIdsMethodId = getMethod(recordClass, "getFieldIds", getFieldMethodSignature("getFieldIds"), false);
    this->getRecordFieldsMethodId = getMethod(recordClass, "getFields", getFieldMethodSignature("getFields"), false);
    this->getRecordFieldMethodId = getMethod(recordClass, "getField", getFieldMethodSignature("getField"), false);
    this->jvm->DeleteLocalRef(recordClass);
}

void MessageApiEndpoint::loadFieldMethodIds()
{
    jclass fieldClass = this->getNamedClass("gov/noaa/messageapi/interfaces/IField");
    this->getFieldIdMethodId = getMethod(fieldClass, "getId", getFieldMethodSignature("getId"), false);
    this->getFieldTypeMethodId = getMethod(fieldClass, "getType", getFieldMethodSignature("getType"), false);
    this->getFieldValueMethodId = getMethod(fieldClass, "getValue", getFieldMethodSignature("getValue"), false);
    this->getFieldIsValidMethodId = getMethod(fieldClass, "isValid", getFieldMethodSignature("isValid"), false);
    this->getFieldIsRequiredMethodId = getMethod(fieldClass, "isRequired", getFieldMethodSignature("isRequired"), false);
    this->jvm->DeleteLocalRef(fieldClass);
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
void MessageApiEndpoint::loadValueTypeMethodIds()
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
    jobject jrecord = static_cast<jobject>(this->jvm->CallObjectMethod(record_list->jrecords, this->getJListItemMethodId, index));
    struct record *record = (struct record *) malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

int MessageApiEndpoint::getJListLength(jobject jList)
{
    return this->jvm->CallIntMethod(jList, this->getJListSizeMethodId);
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

struct string_list *MessageApiEndpoint::getFieldIds(struct record *record)
{
    jobject jFieldIdList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldIdsMethodId);
    struct string_list *field_ids = this->translateFromJavaStringList(jFieldIdList);
    this->jvm->DeleteLocalRef(jFieldIdList);
    return field_ids;
}

struct field_list * MessageApiEndpoint::getFields(struct record *record)
{
    jobject jFieldList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldsMethodId);

    int fieldCount = this->getJListLength(jFieldList);
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
    return field_list;

}

struct field * MessageApiEndpoint::getField(struct record *record, const char *fieldId)
{
    jstring jFieldId = this->toJavaString(fieldId);
    jobject jField = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(struct field) + sizeof(jField));
    field->jfield = jField;
    this->jvm->DeleteLocalRef(jFieldId);
    return field;
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

struct field_value *MessageApiEndpoint::getFieldValue(struct field *field)
{
    jobject jFieldValue = this->jvm->CallObjectMethod(field->jfield, this->getFieldValueMethodId);
    struct field_value *field_value = (struct field_value *)malloc(sizeof(field_value) + sizeof(jFieldValue));
    field_value->jvalue = jFieldValue;
    return field_value;
}

bool MessageApiEndpoint::getFieldIsValid(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->getFieldIsValidMethodId);
}

bool MessageApiEndpoint::getFieldIsRequired(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->getFieldIsRequiredMethodId);
}

int MessageApiEndpoint::fieldValueAsInteger(struct field_value *field_value)
{
    return (int)jvm->CallIntMethod(field_value->jvalue, this->getJIntMethodId);
}
