#ifndef _NATIVECONDITIONUTILS_H
#define _NATIVECONDITIONUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"

/**
 * This is the header for the NativeConditionUtils class. 
 */
class NativeConditionUtils
{

public:
    /*Default constructor/destructors*/
    NativeConditionUtils(JNIEnv *javaEnv, jobject nativeCondition);
    ~NativeConditionUtils();

    /*API Methods*/
    struct val_map *getConstructor();
    struct field *getField();
    struct condition *getCondition();

private:
    /*Vars*/
    JNIEnv *jvm;
    jobject nativeCondition;

    /*Native Condition Methods*/
    jmethodID getConstructorMethodId;
    jmethodID getFieldMethodId;
    jmethodID getConditionMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, jobject nativeCondition);

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
