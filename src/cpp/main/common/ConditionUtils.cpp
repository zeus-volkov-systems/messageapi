#include "ConditionUtils.h"

#include <jni.h>


/**
Constructor for the ConditionUtils object.
*/
ConditionUtils::ConditionUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

ConditionUtils::~ConditionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void ConditionUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void ConditionUtils::loadMethodIds()
{
}