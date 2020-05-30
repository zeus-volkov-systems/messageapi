#include "TransformationUtils.h"

#include <jni.h>

/**
 * Sessions are the top level API container of any given computation. Sessions
 * bootstrap from a specification map and 'lock-in' a computation environment,
 * allowing requests to be created.
 * 
 * @author Ryan Berkheimer
 */

/* Default Constructor */
TransformationUtils::TransformationUtils(JNIEnv *jvm, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, mapUtils, listUtils);
    this->loadMethodIds();
}

/* Default Destructor */
TransformationUtils::~TransformationUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/* Public API */


/* Private Methods */

void TransformationUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->mapUtils = mapUtils;
    this->listUtils = listUtils;
}

void TransformationUtils::loadMethodIds()
{
    jclass transformationClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/ITransformation");

    /*this->createRequestMethodId = JniUtils::getMethod(this->jvm, sessionClass, "createRequest", this->getMethodSignature("createRequest"), false);*/

    jvm->DeleteLocalRef(transformationClass);
}

const char *TransformationUtils::getMethodSignature(const char *methodName)
{
    /*if (strcmp(methodName, "createRequest") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRequest;";
    }*/
    return NULL;
}