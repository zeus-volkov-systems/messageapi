#include "ProtocolRecordUtils.h"

#include <jni.h>


/**
Constructor for a ProtocolRecordUtils object.
*/
ProtocolRecordUtils::ProtocolRecordUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

ProtocolRecordUtils::~ProtocolRecordUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void ProtocolRecordUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void ProtocolRecordUtils::loadMethodIds()
{
}