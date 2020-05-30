#include "FieldUtils.h"

#include <jni.h>


/** Constructor */
FieldUtils::FieldUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

/* Destructor */
FieldUtils::~FieldUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/* Public API */

const char *FieldUtils::getId(struct field *field)
{
    jstring jFieldId = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getIdMethodId));
    const char *fieldId = this->typeUtils->fromJavaString(jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return fieldId;
}

const char *FieldUtils::getType(struct field *field)
{
    jstring jFieldType = static_cast<jstring>(this->jvm->CallObjectMethod(field->jfield, this->getTypeMethodId));
    const char *fieldType = this->typeUtils->fromJavaString(jFieldType);
    this->jvm->DeleteLocalRef(jFieldType);
    return fieldType;
}

bool FieldUtils::isValid(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->isValidMethodId);
}

bool FieldUtils::isRequired(struct field *field)
{
    return (bool)this->jvm->CallBooleanMethod(field->jfield, this->isRequiredMethodId);
}

bool FieldUtils::isNull(struct field *field)
{
    struct val *value = this->getVal(field);
    if (value->jvalue == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct val *FieldUtils::getVal(struct field *field)
{
    jobject jFieldValue = this->jvm->CallObjectMethod(field->jfield, this->getValueMethodId);
    struct val *value = (struct val *)malloc(sizeof(value) + sizeof(jFieldValue));
    value->jvalue = jFieldValue;
    return value;
}

int FieldUtils::getIntVal(struct field *field)
{
    struct val *value = this->getVal(field);
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->typeUtils->getIntMethod());
    return intVal;
}

long FieldUtils::getLongVal(struct field *field)
{
    struct val *value = this->getVal(field);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->typeUtils->getLongMethod());
    return longVal;
}

float FieldUtils::getFloatVal(struct field *field)
{
    struct val *value = this->getVal(field);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->typeUtils->getFloatMethod());
    return floatVal;
}

double FieldUtils::getDoubleVal(struct field *field)
{
    struct val *value = this->getVal(field);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->typeUtils->getDoubleMethod());
    return doubleVal;
}

signed char FieldUtils::getByteVal(struct field *field)
{
    struct val *value = this->getVal(field);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->typeUtils->getByteMethod());
    return (signed char)jByte;
}

const char *FieldUtils::getStringVal(struct field *field)
{
    struct val *value = this->getVal(field);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool FieldUtils::getBoolVal(struct field *field)
{
    struct val *value = this->getVal(field);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->typeUtils->getBoolMethod());
    return boolVal;
}

short FieldUtils::getShortVal(struct field *field)
{
    struct val *value = this->getVal(field);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->typeUtils->getShortMethod());
    return shortVal;
}

struct val_list *FieldUtils::getListVal(struct field *field)
{
    struct val *value = this->getVal(field);
    int itemCount = this->listUtils->getListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = itemCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

void FieldUtils::setVal(struct field *field, struct val *value)
{
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, value->jvalue);
}

void FieldUtils::setIntVal(struct field *field, int value)
{
    jobject jIntVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void FieldUtils::setLongVal(struct field *field, long value)
{
    jobject jLongVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void FieldUtils::setFloatVal(struct field *field, float value)
{
    jobject jFloatVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void FieldUtils::setDoubleVal(struct field *field, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void FieldUtils::setByteVal(struct field *field, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void FieldUtils::setStringVal(struct field *field, const char *value)
{
    jstring jStringVal = this->typeUtils->toJavaString(value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void FieldUtils::setBoolVal(struct field *field, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void FieldUtils::setShortVal(struct field *field, short value)
{
    jobject jShortVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)value);
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, jShortVal);
    this->jvm->DeleteLocalRef(jShortVal);
}

void FieldUtils::setListVal(struct field *field, struct val_list *value)
{
    this->jvm->CallVoidMethod(field->jfield, this->setValueMethodId, value->jlist);
}

/* Private Methods */
void FieldUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void FieldUtils::loadMethodIds()
{
    jclass fieldClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IField");
    this->getIdMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getId", this->getMethodSignature("getId"), false);
    this->getTypeMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getType", this->getMethodSignature("getType"), false);
    this->getValueMethodId = JniUtils::getMethod(this->jvm, fieldClass, "getValue", this->getMethodSignature("getValue"), false);
    this->isValidMethodId = JniUtils::getMethod(this->jvm, fieldClass, "isValid", this->getMethodSignature("isValid"), false);
    this->isRequiredMethodId = JniUtils::getMethod(this->jvm, fieldClass, "isRequired", this->getMethodSignature("isRequired"), false);
    this->setValueMethodId = JniUtils::getMethod(this->jvm, fieldClass, "setValue", this->getMethodSignature("setValue"), false);
    this->jvm->DeleteLocalRef(fieldClass);
}

const char *FieldUtils::getMethodSignature(const char *methodName)
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
        return "()Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "isRequired") == 0)
    {
        return "()Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "setValue") == 0)
    {
        return "(Ljava/lang/Object;)V";
    }
    return NULL;
}
