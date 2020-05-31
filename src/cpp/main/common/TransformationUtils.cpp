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
TransformationUtils::TransformationUtils(JNIEnv *jvm, jobject transformation, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, transformation, typeUtils, mapUtils, listUtils);
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

struct val_map *TransformationUtils::getConstructor() {
    jobject jMap = this->jvm->CallObjectMethod(this->transformation, this->getConstructorMethodId);
    struct val_map *map = (struct val_map *)malloc(sizeof(struct val_map));
    map->jmap = jMap;
    return map;
}


/* Private Methods */

void TransformationUtils::loadGlobalRefs(JNIEnv *jvm, jobject transformation, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->transformation = transformation;
    this->typeUtils = typeUtils;
    this->mapUtils = mapUtils;
    this->listUtils = listUtils;
}

void TransformationUtils::loadMethodIds()
{
    jclass transformationClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/ITransformation");

    this->getConstructorMethodId = JniUtils::getMethod(this->jvm, transformationClass, "getConstructor", this->getMethodSignature("getConstructor"), false);

    jvm->DeleteLocalRef(transformationClass);
}

const char *TransformationUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getConstructor") == 0)
    {
        return "()Ljava/util/Map;";
    }
    return NULL;
}