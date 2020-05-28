#include "FieldUtils.h"

#include <jni.h>


/**
Constructor for the FieldUtils object.
*/
FieldUtils::FieldUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

FieldUtils::~FieldUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void FieldUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void FieldUtils::loadMethodIds()
{
}