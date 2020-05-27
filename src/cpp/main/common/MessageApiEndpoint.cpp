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

    this->typeUtils = new TypeUtils(this->jvm);
    this->listUtils = new ListUtils(this->jvm, typeUtils);
    this->packetUtils = new PacketUtils(this->jvm, this->listUtils);

    this->loadEndpointMethodIds();
    this->loadProtocolRecordMethodIds();
    this->loadRecordMethodIds();
    this->loadRejectionMethodIds();
    this->loadFieldMethodIds();
    this->loadConditionMethodIds();
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        delete this->packetUtils;
        delete this->listUtils;
        delete this->typeUtils;
        this->jvm->DeleteGlobalRef(this->endpoint);
        this->jvm->DeleteGlobalRef(this->protocolRecord);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

PacketUtils *MessageApiEndpoint::getPacketUtils()
{
    return this->packetUtils;
}

ListUtils *MessageApiEndpoint::getListUtils()
{
    return this->listUtils;
}

TypeUtils *MessageApiEndpoint::getTypeUtils()
{
    return this->typeUtils;
}

void MessageApiEndpoint::loadEndpointMethodIds()
{

    jclass endpointClass = JniUtils::getObjectClass(this->jvm, this->endpoint);
    this->getStateContainerMethodId = JniUtils::getMethod(this->jvm, endpointClass, "getStateContainer", this->getEndpointMethodSignature("getStateContainer"), false);
    this->getDefaultFieldsMethodId = JniUtils::getMethod(this->jvm, endpointClass, "getDefaultFields", this->getEndpointMethodSignature("getDefaultFields"), false);
    this->createPacketMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createPacket", this->getEndpointMethodSignature("createPacket"), false);
    this->createRecordMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createRecord", this->getEndpointMethodSignature("createRecord"), false);
    this->createRejectionMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createRejection", this->getEndpointMethodSignature("createRejection"), false);
    this->jvm->DeleteLocalRef(endpointClass);
}

void MessageApiEndpoint::loadProtocolRecordMethodIds()
{

    jclass protocolRecordClass = JniUtils::getObjectClass(this->jvm, this->protocolRecord);
    this->getRecordsMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecords", this->getProtocolRecordMethodSignature("getRecords"), false);
    this->getRecordsByCollectionMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByCollection", this->getProtocolRecordMethodSignature("getRecordsByCollection"), false);
    this->getRecordsByUUIDMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByUUID", this->getProtocolRecordMethodSignature("getRecordsByUUID"), false);
    this->getRecordsByTransformationMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByTransformation", this->getProtocolRecordMethodSignature("getRecordsByTransformation"), false);
    this->getRecordsByClassifierMethodId = JniUtils::getMethod(this->jvm, protocolRecordClass, "getRecordsByClassifier", this->getProtocolRecordMethodSignature("getRecordsByClassifier"), false);
    this->jvm->DeleteLocalRef(protocolRecordClass);
}

void MessageApiEndpoint::loadRecordMethodIds()
{
    jclass recordClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IRecord");
    /*Intrinsic Methods*/
    this->getRecordIsValidMethodId = JniUtils::getMethod(this->jvm, recordClass, "isValid", this->getRecordMethodSignature("isValid"), false);
    this->getRecordCopyMethodId = JniUtils::getMethod(this->jvm, recordClass, "getCopy", this->getRecordMethodSignature("getCopy"), false);
    /*Field Related Methods*/
    this->getRecordFieldIdsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getFieldIds", this->getRecordMethodSignature("getFieldIds"), false);
    this->getRecordFieldsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getFields", this->getRecordMethodSignature("getFields"), false);
    this->getRecordHasFieldMethodId = JniUtils::getMethod(this->jvm, recordClass, "hasField", this->getRecordMethodSignature("hasField"), false);
    this->getRecordFieldMethodId = JniUtils::getMethod(this->jvm, recordClass, "getField", this->getRecordMethodSignature("getField"), false);
    /*Condition Related Methods*/
    this->getRecordConditionIdsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getConditionIds", this->getRecordMethodSignature("getConditionIds"), false);
    this->getRecordConditionsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getConditions", this->getRecordMethodSignature("getConditions"), false);
    this->getRecordHasConditionMethodId = JniUtils::getMethod(this->jvm, recordClass, "hasCondition", this->getRecordMethodSignature("hasCondition"), false);
    this->getRecordConditionMethodId = JniUtils::getMethod(this->jvm, recordClass, "getCondition", this->getRecordMethodSignature("getCondition"), false);
    this->jvm->DeleteLocalRef(recordClass);
}

void MessageApiEndpoint::loadRejectionMethodIds()
{
    jclass rejectionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IRejection");
    this->getRejectionCopyMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getCopy", this->getRejectionMethodSignature("getCopy"), false);
    this->getRejectionReasonsMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getReasons", this->getRejectionMethodSignature("getReasons"), false);
    this->getRejectionRecordMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getRecord", this->getRejectionMethodSignature("getRecord"), false);
    this->addRejectionReasonMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "addReason", this->getRejectionMethodSignature("addReason"), false);
    this->jvm->DeleteLocalRef(rejectionClass);
}

void MessageApiEndpoint::loadFieldMethodIds()
{
    jclass fieldClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IField");
    this->getFieldIdMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getId", this->getFieldMethodSignature("getId"), false);
    this->getFieldTypeMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getType", this->getFieldMethodSignature("getType"), false);
    this->getFieldValueMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getValue", this->getFieldMethodSignature("getValue"), false);
    this->getFieldIsValidMethodId = JniUtils::getMethod(this->jvm, fieldClass, "isValid", this->getFieldMethodSignature("isValid"), false);
    this->getFieldIsRequiredMethodId = JniUtils::getMethod(this->jvm, fieldClass, "isRequired", this->getFieldMethodSignature("isRequired"), false);
    this->setFieldValueMethodId = JniUtils::getMethod(this->jvm, fieldClass, "setValue", this->getFieldMethodSignature("setValue"), false);
    this->jvm->DeleteLocalRef(fieldClass);
}

void MessageApiEndpoint::loadConditionMethodIds()
{
    jclass conditionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/ICondition");
    this->getConditionIdMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getId", this->getConditionMethodSignature("getId"), false);
    this->getConditionTypeMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getType", this->getConditionMethodSignature("getType"), false);
    this->getConditionOperatorMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getOperator", this->getConditionMethodSignature("getOperator"), false);
    this->getConditionValueMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getValue", this->getConditionMethodSignature("getValue"), false);
    this->setConditionValueMethodId = JniUtils::getMethod(this->jvm, conditionClass, "setValue", this->getConditionMethodSignature("setValue"), false);
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

    int fieldCount = this->listUtils->getListLength(jFieldList);
    struct field **fields = (struct field **)malloc(sizeof(struct field *) * fieldCount);

    for (int i = 0; i < fieldCount; i++)
    {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->listUtils->getListItemMethod(), i));
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
    jstring jreason = this->typeUtils->toJavaString(reason);
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

struct record_list * MessageApiEndpoint::getRecords(const char *recordMethod, const char *key, const char *val)
{
    jobject jprotocolRecords = this->getProtocolRecords(recordMethod, key, val);
    int recordCount = this->listUtils->getListLength(jprotocolRecords);
    struct record_list *record_list = (struct record_list *) malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jprotocolRecords;

    return record_list;
}

struct record *MessageApiEndpoint::getRecord(struct record_list *record_list, int index)
{
    jobject jrecord = this->jvm->CallObjectMethod(record_list->jrecords, this->listUtils->getListItemMethod(), index);
    struct record *record = (struct record *) malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
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
    jstring jFieldId = this->typeUtils->toJavaString(fieldId);
    bool hasJField = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->getRecordHasFieldMethodId, jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return hasJField;
}
struct string_list *MessageApiEndpoint::getFieldIds(struct record *record)
{
    jobject jFieldIdList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldIdsMethodId);
    struct string_list *field_ids = this->listUtils->translateStringList(jFieldIdList);
    this->jvm->DeleteLocalRef(jFieldIdList);
    return field_ids;
}
struct field_list *MessageApiEndpoint::getFields(struct record *record)
{
    jobject jFieldList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldsMethodId);

    int fieldCount = this->listUtils->getListLength(jFieldList);
    struct field **fields = (struct field **)malloc(sizeof(struct field *) * fieldCount);

    for (int i = 0; i < fieldCount; i++)
    {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->listUtils->getListItemMethod(), i));
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
    jstring jFieldId = this->typeUtils->toJavaString(fieldId);
    jobject jField = this->jvm->CallObjectMethod(record->jrecord, this->getRecordFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(struct field) + sizeof(jField));
    field->jfield = jField;
    this->jvm->DeleteLocalRef(jFieldId);
    return field;
}

bool MessageApiEndpoint::getRecordHasCondition(struct record *record, const char *conditionId)
{
    jstring jConditionId = this->typeUtils->toJavaString(conditionId);
    bool hasJCondition = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->getRecordHasConditionMethodId, jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return hasJCondition;
}

struct string_list *MessageApiEndpoint::getConditionIds(struct record *record)
{
    jobject jConditionIdList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionIdsMethodId);
    struct string_list *condition_ids = this->listUtils->translateStringList(jConditionIdList);
    this->jvm->DeleteLocalRef(jConditionIdList);
    return condition_ids;
}

struct condition_list *MessageApiEndpoint::getConditions(struct record *record)
{
    jobject jConditionList = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionsMethodId);

    int conditionCount = this->listUtils->getListLength(jConditionList);
    struct condition **conditions = (struct condition **)malloc(sizeof(struct condition *) * conditionCount);

    for (int i = 0; i < conditionCount; i++)
    {
        jobject jcondition = static_cast<jobject>(this->jvm->CallObjectMethod(jConditionList, this->listUtils->getListItemMethod(), i));
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
    jstring jConditionId = this->typeUtils->toJavaString(conditionId);
    jobject jCondition = this->jvm->CallObjectMethod(record->jrecord, this->getRecordConditionMethodId, jConditionId);
    struct condition *condition = (struct condition *)malloc(sizeof(struct condition) + sizeof(jCondition));
    condition->jcondition = jCondition;
    this->jvm->DeleteLocalRef(jConditionId);
    return condition;
}

const char *MessageApiEndpoint::getFieldId(struct field *field)
{
    jstring jFieldId = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getFieldIdMethodId));
    const char *fieldId = this->typeUtils->fromJavaString(jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return fieldId;
}

const char *MessageApiEndpoint::getFieldType(struct field *field)
{
    jstring jFieldType = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getFieldTypeMethodId));
    const char *fieldType = this->typeUtils->fromJavaString(jFieldType);
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
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->typeUtils->getIntMethod());
    return intVal;
}

long MessageApiEndpoint::getFieldLongVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->typeUtils->getLongMethod());
    return longVal;
}

float MessageApiEndpoint::getFieldFloatVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->typeUtils->getFloatMethod());
    return floatVal;
}

double MessageApiEndpoint::getFieldDoubleVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->typeUtils->getDoubleMethod());
    return doubleVal;
}

signed char MessageApiEndpoint::getFieldByteVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->typeUtils->getByteMethod());
    return (signed char)jByte;
}

const char *MessageApiEndpoint::getFieldStringVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool MessageApiEndpoint::getFieldBoolVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->typeUtils->getBoolMethod());
    return boolVal;
}

short MessageApiEndpoint::getFieldShortVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->typeUtils->getShortMethod());
    return shortVal;
}

struct val_list *MessageApiEndpoint::getFieldListVal(struct field *field)
{
    struct val *value = this->getFieldVal(field);
    int itemCount = this->listUtils->getListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = itemCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

void MessageApiEndpoint::setFieldVal(struct field *field, struct val *value)
{
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, value->jvalue);
}

void MessageApiEndpoint::setFieldIntVal(struct field *field, int value)
{
    jobject jIntVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void MessageApiEndpoint::setFieldLongVal(struct field *field, long value)
{
    jobject jLongVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void MessageApiEndpoint::setFieldFloatVal(struct field *field, float value)
{
    jobject jFloatVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void MessageApiEndpoint::setFieldDoubleVal(struct field *field, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void MessageApiEndpoint::setFieldByteVal(struct field *field, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void MessageApiEndpoint::setFieldStringVal(struct field *field, const char *value)
{
    jstring jStringVal = this->typeUtils->toJavaString(value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void MessageApiEndpoint::setFieldBoolVal(struct field *field, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)value);
    this->jvm->CallVoidMethod(field->jfield, this->setFieldValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void MessageApiEndpoint::setFieldShortVal(struct field *field, short value)
{
    jobject jShortVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)value);
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
    const char *conditionId = this->typeUtils->fromJavaString(jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return conditionId;
}

const char *MessageApiEndpoint::getConditionType(struct condition *condition)
{
    jstring jConditionType = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getConditionTypeMethodId));
    const char *conditionType = this->typeUtils->fromJavaString(jConditionType);
    this->jvm->DeleteLocalRef(jConditionType);
    return conditionType;
}

const char *MessageApiEndpoint::getConditionOperator(struct condition *condition)
{
    jstring jConditionOperator = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getConditionOperatorMethodId));
    const char *conditionOperator = this->typeUtils->fromJavaString(jConditionOperator);
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
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->typeUtils->getIntMethod());
    return intVal;
}

long MessageApiEndpoint::getConditionLongVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->typeUtils->getLongMethod());
    return longVal;
}

float MessageApiEndpoint::getConditionFloatVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->typeUtils->getFloatMethod());
    return floatVal;
}

double MessageApiEndpoint::getConditionDoubleVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->typeUtils->getDoubleMethod());
    return doubleVal;
}

signed char MessageApiEndpoint::getConditionByteVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->typeUtils->getByteMethod());
    return (signed char)jByte;
}

const char *MessageApiEndpoint::getConditionStringVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool MessageApiEndpoint::getConditionBoolVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->typeUtils->getBoolMethod());
    return boolVal;
}

short MessageApiEndpoint::getConditionShortVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->typeUtils->getShortMethod());
    return shortVal;
}

struct val_list *MessageApiEndpoint::getConditionListVal(struct condition *condition)
{
    struct val *value = this->getConditionVal(condition);
    int itemCount = this->listUtils->getListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = itemCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

void MessageApiEndpoint::setConditionVal(struct condition *condition, struct val *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, value->jvalue);
}

void MessageApiEndpoint::setConditionIntVal(struct condition *condition, int value)
{
    jobject jIntVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void MessageApiEndpoint::setConditionLongVal(struct condition *condition, long value)
{
    jobject jLongVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void MessageApiEndpoint::setConditionFloatVal(struct condition *condition, float value)
{
    jobject jFloatVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void MessageApiEndpoint::setConditionDoubleVal(struct condition *condition, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void MessageApiEndpoint::setConditionByteVal(struct condition *condition, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void MessageApiEndpoint::setConditionStringVal(struct condition *condition, const char *value)
{
    jstring jStringVal = this->typeUtils->toJavaString(value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void MessageApiEndpoint::setConditionBoolVal(struct condition *condition, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void MessageApiEndpoint::setConditionShortVal(struct condition *condition, short value)
{
    jobject jShortVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, jShortVal);
    this->jvm->DeleteLocalRef(jShortVal);
}

void MessageApiEndpoint::setConditionListVal(struct condition *condition, struct val_list *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setConditionValueMethodId, value->jlist);
}

struct record_list *MessageApiEndpoint::createRecordList()
{
    jobject jList = this->jvm->NewObject(this->typeUtils->getListClass(), this->listUtils->createListMethod());
    //would change previous to
    //jobject jList = this->jvm->NewObject(this->listUtils->getListClass(), this->listUtils->getCreateListMethodId());
    //then we would need to add the following to the MessageApi Constructor:
    //this->recordUtils = new RecordUtils(this->jvm, this->listUtils)
    //then, in the RecordUtils class, we set this->listUtils = listUtils
    //remember to also add a delete listUtils on the pointer in the Destructor for Record Utils
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = 0;
    record_list->jrecords = jList;
    return record_list;
}

void MessageApiEndpoint::addRecord(struct record_list *record_list, struct record *record)
{
    this->jvm->CallVoidMethod(record_list->jrecords, this->listUtils->addListItemMethod(), record->jrecord);
    record_list->count += 1;
}

struct rejection_list *MessageApiEndpoint::createRejectionList()
{
    jobject jList = this->jvm->NewObject(this->typeUtils->getListClass(), this->listUtils->createListMethod());
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = 0;
    rejection_list->jrejections = jList;
    return rejection_list;
}

void MessageApiEndpoint::addRejection(struct rejection_list *rejection_list, struct rejection *rejection)
{
    this->jvm->CallVoidMethod(rejection_list->jrejections, this->listUtils->addListItemMethod(), rejection->jrejection);
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
    struct string_list *reasons = this->listUtils->translateStringList(jReasons);
    return reasons;
}

void MessageApiEndpoint::addRejectionReason(struct rejection *rejection, const char *reason)
{
    jstring jReason = this->typeUtils->toJavaString(reason);
    this->jvm->CallVoidMethod(rejection->jrejection, this->addRejectionReasonMethodId, jReason);
}

