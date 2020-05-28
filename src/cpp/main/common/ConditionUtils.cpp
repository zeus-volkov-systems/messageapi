#include "ConditionUtils.h"

#include <jni.h>


/* Default Constructor */
ConditionUtils::ConditionUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

/* Destructor */
ConditionUtils::~ConditionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

const char *ConditionUtils::getId(struct condition *condition)
{
    jstring jConditionId = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getIdMethodId));
    const char *conditionId = this->typeUtils->fromJavaString(jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return conditionId;
}

const char *ConditionUtils::getType(struct condition *condition)
{
    jstring jConditionType = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getTypeMethodId));
    const char *conditionType = this->typeUtils->fromJavaString(jConditionType);
    this->jvm->DeleteLocalRef(jConditionType);
    return conditionType;
}

const char *ConditionUtils::getOperator(struct condition *condition)
{
    jstring jConditionOperator = static_cast<jstring>(this->jvm->CallObjectMethod(condition->jcondition, this->getOperatorMethodId));
    const char *conditionOperator = this->typeUtils->fromJavaString(jConditionOperator);
    this->jvm->DeleteLocalRef(jConditionOperator);
    return conditionOperator;
}

bool ConditionUtils::isNull(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    if (value->jvalue == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct val *ConditionUtils::getVal(struct condition *condition)
{
    jobject jConditionValue = this->jvm->CallObjectMethod(condition->jcondition, this->getValueMethodId);
    struct val *value = (struct val *)malloc(sizeof(value) + sizeof(jConditionValue));
    value->jvalue = jConditionValue;
    return value;
}

int ConditionUtils::getIntVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    int intVal = (int)this->jvm->CallIntMethod(value->jvalue, this->typeUtils->getIntMethod());
    return intVal;
}

long ConditionUtils::getLongVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    long longVal = (long)this->jvm->CallLongMethod(value->jvalue, this->typeUtils->getLongMethod());
    return longVal;
}

float ConditionUtils::getFloatVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    float floatVal = (float)this->jvm->CallFloatMethod(value->jvalue, this->typeUtils->getFloatMethod());
    return floatVal;
}

double ConditionUtils::getDoubleVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    double doubleVal = (double)this->jvm->CallDoubleMethod(value->jvalue, this->typeUtils->getDoubleMethod());
    return doubleVal;
}

signed char ConditionUtils::getByteVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    jbyte jByte = this->jvm->CallByteMethod(value->jvalue, this->typeUtils->getByteMethod());
    return (signed char)jByte;
}

const char *ConditionUtils::getStringVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    jstring jString = (jstring)value->jvalue;
    const char *returnString = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return returnString;
}

bool ConditionUtils::getBoolVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    bool boolVal = (bool)jvm->CallBooleanMethod(value->jvalue, this->typeUtils->getBoolMethod());
    return boolVal;
}

short ConditionUtils::getShortVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    short shortVal = (short)this->jvm->CallShortMethod(value->jvalue, this->typeUtils->getShortMethod());
    return shortVal;
}

struct val_list *ConditionUtils::getListVal(struct condition *condition)
{
    struct val *value = this->getVal(condition);
    int itemCount = this->listUtils->getListLength(value->jvalue);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = itemCount;
    valueList->jlist = value->jvalue;
    return valueList;
}

void ConditionUtils::setVal(struct condition *condition, struct val *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, value->jvalue);
}

void ConditionUtils::setIntVal(struct condition *condition, int value)
{
    jobject jIntVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jIntVal);
    this->jvm->DeleteLocalRef(jIntVal);
}

void ConditionUtils::setLongVal(struct condition *condition, long value)
{
    jobject jLongVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jLongVal);
    this->jvm->DeleteLocalRef(jLongVal);
}

void ConditionUtils::setFloatVal(struct condition *condition, float value)
{
    jobject jFloatVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jFloatVal);
    this->jvm->DeleteLocalRef(jFloatVal);
}

void ConditionUtils::setDoubleVal(struct condition *condition, double value)
{
    jobject jDoubleVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jDoubleVal);
    this->jvm->DeleteLocalRef(jDoubleVal);
}

void ConditionUtils::setByteVal(struct condition *condition, signed char value)
{
    jobject jByteVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jByteVal);
    this->jvm->DeleteLocalRef(jByteVal);
}

void ConditionUtils::setStringVal(struct condition *condition, const char *value)
{
    jstring jStringVal = this->typeUtils->toJavaString(value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jStringVal);
    this->jvm->DeleteLocalRef(jStringVal);
}

void ConditionUtils::setBoolVal(struct condition *condition, bool value)
{
    jobject jBoolVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

void ConditionUtils::setShortVal(struct condition *condition, short value)
{
    jobject jShortVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)value);
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, jShortVal);
    this->jvm->DeleteLocalRef(jShortVal);
}

void ConditionUtils::setListVal(struct condition *condition, struct val_list *value)
{
    this->jvm->CallVoidMethod(condition->jcondition, this->setValueMethodId, value->jlist);
}

/* Private Methods */
void ConditionUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void ConditionUtils::loadMethodIds()
{
    jclass conditionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/ICondition");
    this->getIdMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getId", this->getMethodSignature("getId"), false);
    this->getTypeMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getType", this->getMethodSignature("getType"), false);
    this->getOperatorMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getOperator", this->getMethodSignature("getOperator"), false);
    this->getValueMethodId = JniUtils::getMethod(this->jvm, conditionClass, "getValue", this->getMethodSignature("getValue"), false);
    this->setValueMethodId = JniUtils::getMethod(this->jvm, conditionClass, "setValue", this->getMethodSignature("setValue"), false);
    this->jvm->DeleteLocalRef(conditionClass);
}

const char *ConditionUtils::getMethodSignature(const char *methodName)
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