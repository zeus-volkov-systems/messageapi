#include "RejectionUtils.h"

#include <jni.h>


/**
Constructor for the RejectionUtils object.
*/
RejectionUtils::RejectionUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

RejectionUtils::~RejectionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void RejectionUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void RejectionUtils::loadMethodIds()
{
}