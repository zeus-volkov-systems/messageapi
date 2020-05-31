#ifndef _TRANSFORMATIONUTILS_H
#define _TRANSFORMATIONUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "TypeUtils.h"
#include "MapUtils.h"
#include "ListUtils.h"

/**
 * 
 * @author Ryan Berkheimer
 */
class TransformationUtils
{

public:
    /*Default constructor */
    TransformationUtils(JNIEnv *jvm, jobject transformation, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils);

    /*Default Destructor */
    ~TransformationUtils();

    /* Transformation API */
    struct val_map *getConstructor();

private:
    /*Vars*/
    JNIEnv *jvm;
    jobject transformation;
    TypeUtils *typeUtils;
    MapUtils *mapUtils;
    ListUtils *listUtils;

    jmethodID getConstructorMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, jobject transformation, TypeUtils *typeUtils, MapUtils *mapUtils, ListUtils *listUtils);

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getMethodSignature(const char *methodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
