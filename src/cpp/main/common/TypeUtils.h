
#ifndef _TYPEUTILS_H
#define _TYPEUTILS_H

#include <jni.h>

#ifdef __cplusplus

#include <stdlib.h>
#include <iostream>

/**
 * This is the header for the TypeUtils object class. TypeUtils contains a set of methods used for manipulation of Java Lists
 * in C++ or C code. TypeUtils is a class to be instantiated so that it remains thread safe for implementors and holds onto 
 * global instances of JVM specific class references and method ids based on those classes.
 */
class TypeUtils
{

public:
    /* Default constructor for TypeUtils */
    TypeUtils(JNIEnv *env);

    /* Default destructor for TypeUtils */
    ~TypeUtils();

    /* Accessors for method ids*/
    jmethodID getBoolMethod();
    jmethodID getByteMethod();
    jmethodID getIntMethod();
    jmethodID getLongMethod();
    jmethodID getFloatMethod();
    jmethodID getDoubleMethod();
    jmethodID getShortMethod();
    jmethodID createBoolMethod();
    jmethodID createByteMethod();
    jmethodID createIntMethod();
    jmethodID createLongMethod();
    jmethodID createFloatMethod();
    jmethodID createDoubleMethod();
    jmethodID createShortMethod();

    /* Accessors for classes */
    jclass getIntClass();
    jclass getLongClass();
    jclass getFloatClass();
    jclass getDoubleClass();
    jclass getByteClass();
    jclass getStringClass();
    jclass getBoolClass();
    jclass getShortClass();

    jclass getListClass();

    jstring toJavaString(const char *charString);
    const char *fromJavaString(jstring javaString);

private:
    JNIEnv *jvm;
    /* Initialization Methods */
    void loadGlobalRefs(JNIEnv *env);
    void loadMethodIds();

    jclass intClass;
    jclass longClass;
    jclass floatClass;
    jclass doubleClass;
    jclass byteClass;
    jclass stringClass;
    jclass boolClass;
    jclass shortClass;

    jclass listClass;

    /*Type Utility Retrieval Methods*/
    jmethodID getBoolMethodId;
    jmethodID getByteMethodId;
    jmethodID getIntMethodId;
    jmethodID getLongMethodId;
    jmethodID getFloatMethodId;
    jmethodID getDoubleMethodId;
    jmethodID getShortMethodId;

    /*Type Utility Creation Methods*/
    jmethodID createBoolMethodId;
    jmethodID createByteMethodId;
    jmethodID createIntMethodId;
    jmethodID createLongMethodId;
    jmethodID createFloatMethodId;
    jmethodID createDoubleMethodId;
    jmethodID createShortMethodId;
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
