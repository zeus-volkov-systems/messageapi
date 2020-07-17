#include "TransformationUtils.h"

#include <jni.h>

/**
 * @author Ryan Berkheimer
 */

/* Default Constructor */
TransformationUtils::TransformationUtils(JNIEnv *jvm, jobject transformation, jobject transformationMap, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, transformation, transformationMap, typeUtils, mapUtils, listUtils);
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

struct val_map *TransformationUtils::getConstructor()
{
    jobject jMap = this->jvm->CallObjectMethod(this->transformation, this->getConstructorMethodId);
    struct val_map *map = (struct val_map *)malloc(sizeof(struct val_map));
    map->jmap = jMap;
    return map;
}

struct record_list *TransformationUtils::getRecords(const char *key)
{
    jobject jList = this->mapUtils->getObjectVal(this->tMap, key);
    int count = this->listUtils->getListLength(jList);
    struct record_list *records = (struct record_list *)malloc(sizeof(struct record_list));
    records->count = count;
    records->jrecords = jList;
    return records;
}

/* Private Methods */

void TransformationUtils::loadGlobalRefs(JNIEnv *jvm, jobject transformation, jobject transformationMap, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->transformation = transformation;
    this->transformationMap = transformationMap;
    this->typeUtils = typeUtils;
    this->mapUtils = mapUtils;
    this->listUtils = listUtils;

    struct val_map *map = (struct val_map *)malloc(sizeof(struct val_map));
    map->jmap = transformationMap;
    this->tMap = map;
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