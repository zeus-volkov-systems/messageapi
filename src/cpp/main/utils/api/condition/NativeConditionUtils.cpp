#include "NativeConditionUtils.h"

#include <jni.h>


/* Default Constructor */
NativeConditionUtils::NativeConditionUtils(JNIEnv *jvm, jobject nativeCondition)
{
    this->loadGlobalRefs(jvm, nativeCondition);
    this->loadMethodIds();
}

/* Destructor */
NativeConditionUtils::~NativeConditionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

struct val_map *NativeConditionUtils::getConstructor()
{
    jobject jMap = this->jvm->CallObjectMethod(this->nativeCondition, this->getConstructorMethodId);
    struct val_map *map = (struct val_map *)malloc(sizeof(struct val_map));
    map->jmap = jMap;
    return map;
}

struct field *NativeConditionUtils::getField()
{
    jobject jField = this->jvm->CallObjectMethod(this->nativeCondition, this->getFieldMethodId);
    struct field *field = (struct field *)malloc(sizeof(struct field));
    field->jfield = jField;
    return field;
}

struct condition *NativeConditionUtils::getCondition()
{
    jobject jCondition = this->jvm->CallObjectMethod(this->nativeCondition, this->getConditionMethodId);
    struct condition *condition = (struct condition *)malloc(sizeof(struct condition));
    condition->jcondition = jCondition;
    return condition;
}

/* Private Methods */
void NativeConditionUtils::loadGlobalRefs(JNIEnv *jvm, jobject nativeCondition)
{
    this->jvm = jvm;
    this->nativeCondition = nativeCondition;
}

void NativeConditionUtils::loadMethodIds()
{
    jclass nativeConditionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/conditions/NativeCondition");
    this->getConstructorMethodId = JniUtils::getMethod(this->jvm, nativeConditionClass, "getConstructor", this->getMethodSignature("getConstructor"), false);
    this->getFieldMethodId = JniUtils::getMethod(this->jvm, nativeConditionClass, "getField", this->getMethodSignature("getField"), false);
    this->getConditionMethodId = JniUtils::getMethod(this->jvm, nativeConditionClass, "getCondition", this->getMethodSignature("getCondition"), false);
    this->jvm->DeleteLocalRef(nativeConditionClass);
}

const char *NativeConditionUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getField") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IField;";
    }
    else if (strcmp(methodName, "getCondition") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/ICondition;";
    }
    else if (strcmp(methodName, "getConstructor") == 0)
    {
        return "()Ljava/util/Map;";
    }
    return NULL;
}