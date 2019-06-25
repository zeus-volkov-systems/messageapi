
#ifndef _Included_NativeTask
#define _Included_NativeTask

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

/**
 * @author Ryan Berkheimer
 */
class MessageApiNativeLib
{

public:
    MessageApiNativeLib(JNIEnv *env, jobject clazz, jobject record);
    ~MessageApiNativeLib();

    void init();

    void checkAndThrow(const char *);

    JNIEnv *getJVM();
    jclass getNamedClass(const char *);
    jclass getObjectClass(jobject);
    jmethodID getMethod(jclass, const char *, const char *, bool);
    jstring toJavaString(const char *);
    const char *fromJavaString(jstring);


private:
    JNIEnv *jvm;
    jobject task;
    jobject data;
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
