#include "RecordUtils.h"

#include <jni.h>


/**
Constructor for the RecordUtils object.
*/
RecordUtils::RecordUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

RecordUtils::~RecordUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void RecordUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void RecordUtils::loadMethodIds()
{
}