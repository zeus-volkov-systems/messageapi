#include "JniUtils.h"

namespace JniUtils
{

    void checkAndThrow(JNIEnv *jvm, std::string errorMessage)
    {
        if (jvm->ExceptionCheck())
        {
            std::cout << "An exception was thrown with the following message:" << errorMessage << std::endl;
            jclass jException = static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass("java/lang/Exception")));
            jvm->ThrowNew(jException, errorMessage.c_str());
            jvm->DeleteLocalRef(jException);
        }
    }

    jclass getNamedClass(JNIEnv *jvm, const char *className)
    {
        jclass clazz = jvm->FindClass(className);
        const char *msg = "getNamedClass> failed for class:";
        std::string buf(msg);
        buf.append(className);
        checkAndThrow(jvm, buf);
        return clazz;
    }

    jclass getGlobalClassRef(JNIEnv *jvm, const char *classname)
    {
        return static_cast<jclass>(jvm->NewGlobalRef(jvm->FindClass(classname)));
    }

    jclass getObjectClass(JNIEnv *jvm, jobject obj)
    {
        jobject objRef = jvm->NewLocalRef(obj);
        jclass clazz = jvm->GetObjectClass(objRef);
        jvm->DeleteLocalRef(objRef);
        const char *msg = "getObjectClass> failed.";
        std::string buf(msg);
        checkAndThrow(jvm, buf);
        return clazz;
    }

    jmethodID getMethod(JNIEnv *jvm, jclass clazz, const char *name, const char *signature, bool isStatic)
    {
        jmethodID id = NULL;
        if (isStatic)
        {
            id = jvm->GetStaticMethodID(clazz, name, signature);
        }
        else
        {
            id = jvm->GetMethodID(clazz, name, signature);
        }

        const char *msg = "getMethod> jMethodID lookup failed.";
        std::string buf(msg);
        buf.append(name);
        checkAndThrow(jvm, buf);
        return id;
    }

} /*namespace JniUtils*/