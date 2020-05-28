
#ifndef _RECORDUTILS_H
#define _RECORDUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"

/**
 * This is the header for the RecordUtils class. 
 * A record contains fields and conditions.
 */
class RecordUtils
{

public:
    /*Default constructor/destructors*/
    RecordUtils(JNIEnv *javaEnv, ListUtils *listUtils);
    ~RecordUtils();

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, ListUtils *listUtils);

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
