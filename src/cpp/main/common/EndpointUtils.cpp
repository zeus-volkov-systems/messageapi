#include "EndpointUtils.h"

#include <jni.h>


/**
Constructor for the Endpoint object.
*/
EndpointUtils::EndpointUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

EndpointUtils::~EndpointUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void EndpointUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void EndpointUtils::loadMethodIds()
{
}