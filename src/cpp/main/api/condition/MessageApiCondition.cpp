#include "MessageApiCondition.h"

#include <iostream>
#include <string>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Constructor for the MessageApiCondition object. Takes a JNI environment pointer, a condition context (this refers to
the condition class that's instantiating the object), a field object, and a condition object.
*/
MessageApiCondition::MessageApiCondition(JNIEnv *env, jobject jNativeCondition, jobject jField, jobject jCondition)
{
    this->jvm = env;
    this->nativeCondition = this->jvm->NewGlobalRef(jNativeCondition);
    this->field = this->jvm->NewGlobalRef(jField);
    this->condition = this->jvm->NewGlobalRef(jCondition);

    this->typeUtils = new TypeUtils(this->jvm);
    this->listUtils = new ListUtils(this->jvm, typeUtils);
    this->mapUtils = new MapUtils(this->jvm, typeUtils);
    this->fieldUtils = new FieldUtils(this->jvm, this->typeUtils, this->listUtils, this->mapUtils);
    this->conditionUtils = new ConditionUtils(this->jvm, this->typeUtils, this->listUtils, this->mapUtils);
    this->nativeConditionUtils = new NativeConditionUtils(this->jvm, this->nativeCondition);
}

MessageApiCondition::~MessageApiCondition()
{
    try
    {
        delete this->fieldUtils;
        delete this->conditionUtils;
        delete this->nativeConditionUtils;
        delete this->listUtils;
        delete this->mapUtils;
        delete this->typeUtils;
        this->jvm->DeleteGlobalRef(this->field);
        this->jvm->DeleteGlobalRef(this->condition);
        this->jvm->DeleteGlobalRef(this->nativeCondition);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

FieldUtils *MessageApiCondition::getFieldUtils()
{
    return this->fieldUtils;
}

ConditionUtils *MessageApiCondition::getConditionUtils()
{
    return this->conditionUtils;
}

NativeConditionUtils *MessageApiCondition::getNativeConditionUtils()
{
    return this->nativeConditionUtils;
}

ListUtils *MessageApiCondition::getListUtils()
{
    return this->listUtils;
}

MapUtils *MessageApiCondition::getMapUtils()
{
    return this->mapUtils;
}

TypeUtils *MessageApiCondition::getTypeUtils()
{
    return this->typeUtils;
}



