
#ifndef _JNIUTILS_H
#define _JNIUTILS_H

#include <jni.h>
#include <string.h>

#ifdef __cplusplus
#include <iostream>
#include <stdlib.h>

/**
 * The JniUtils namespace contains methods for general use for JNI interoperability,
 * such as retrieving classes, method ids, and throwing java errors.
 */
namespace JniUtils
{

    /*Handles errors allowing throws in java code.*/
    void checkAndThrow(JNIEnv *jvm, std::string errorMessage);

    /*Return a jclass for the provided class name and the jvm context. The passed jvm must have the class loaded already in the classpath.*/
    jclass getNamedClass(JNIEnv *jvm, const char *javaClassName);

    /*Returns a global class ref from JNI using a static cast. The global ref needs to be explicitly removed.*/
    jclass getGlobalClassRef(JNIEnv *jvm, const char *classname);

    /*Return a jclass for the provided jobject held by the provided jvm context.*/
    jclass getObjectClass(JNIEnv *jvm, jobject javaObject);

    /*Lookup a java methodID for the given class, method name, and signature string. Also pass in whether method is class static or not.*/
    jmethodID getMethod(JNIEnv *jvm, jclass javaClass, const char *methodName, const char *methodSignature, bool isStatic);

} /*namespace JniUtils*/

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
