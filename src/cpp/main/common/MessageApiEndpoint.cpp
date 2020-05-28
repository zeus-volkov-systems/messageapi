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
    this->endpointUtils = new EndpointUtils(this->jvm, this->endpoint, this->typeUtils, this->listUtils);
    this->protocolRecordUtils = new ProtocolRecordUtils(this->jvm, this->protocolRecord, this->typeUtils, this->listUtils);
    this->recordUtils = new RecordUtils(this->jvm, this->typeUtils, this->listUtils);
    this->rejectionUtils = new RejectionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->packetUtils = new PacketUtils(this->jvm, this->listUtils);

    this->loadFieldMethodIds();
    this->loadConditionMethodIds();
}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        delete this->endpointUtils;
        delete this->protocolRecordUtils;
        delete this->recordUtils;
        delete this->rejectionUtils;
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

EndpointUtils *MessageApiEndpoint::getEndpointUtils()
{
    return this->endpointUtils;
}

ProtocolRecordUtils *MessageApiEndpoint::getProtocolRecordUtils()
{
    return this->protocolRecordUtils;
}

RecordUtils *MessageApiEndpoint::getRecordUtils()
{
    return this->recordUtils;
}

RejectionUtils *MessageApiEndpoint::getRejectionUtils()
{
    return this->rejectionUtils;
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


