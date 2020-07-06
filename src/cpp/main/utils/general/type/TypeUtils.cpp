#include "TypeUtils.h"

TypeUtils::TypeUtils(JNIEnv *env)
{
    this->loadGlobalRefs(env);
    this->loadMethodIds();
}

TypeUtils::~TypeUtils()
{
    try
    {
        this->jvm->DeleteGlobalRef(this->mapClass);
        this->jvm->DeleteGlobalRef(this->listClass);
        this->jvm->DeleteGlobalRef(this->intClass);
        this->jvm->DeleteGlobalRef(this->longClass);
        this->jvm->DeleteGlobalRef(this->floatClass);
        this->jvm->DeleteGlobalRef(this->doubleClass);
        this->jvm->DeleteGlobalRef(this->byteClass);
        this->jvm->DeleteGlobalRef(this->stringClass);
        this->jvm->DeleteGlobalRef(this->boolClass);
        this->jvm->DeleteGlobalRef(this->shortClass);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void TypeUtils::loadGlobalRefs(JNIEnv *env)
{
    this->jvm = env;

    this->mapClass = JniUtils::getGlobalClassRef(env, "java/util/HashMap");
    this->listClass = JniUtils::getGlobalClassRef(env, "java/util/ArrayList");

    this->intClass = JniUtils::getGlobalClassRef(env, "java/lang/Integer");
    this->longClass = JniUtils::getGlobalClassRef(env, "java/lang/Long");
    this->floatClass = JniUtils::getGlobalClassRef(env, "java/lang/Float");
    this->doubleClass = JniUtils::getGlobalClassRef(env, "java/lang/Double");
    this->byteClass = JniUtils::getGlobalClassRef(env, "java/lang/Byte");
    this->stringClass = JniUtils::getGlobalClassRef(env, "java/lang/String");
    this->boolClass = JniUtils::getGlobalClassRef(env, "java/lang/Boolean");
    this->shortClass = JniUtils::getGlobalClassRef(env, "java/lang/Short");
}

/**
 * Loads the default value types for ListUtils.
 * Default types are relatively primitive data types. More complicated 'struct' types
 * will require extension of this by user methods.
 * The included default types have associated access,modification,and release methods.
 * Each also has an associated 'list' method (i.e., string has string_list, byte has byte_list, etc.)
 * Default types include the following:
 * integer, long, float, double, string, byte, boolean
 */
void TypeUtils::loadMethodIds()
{

    this->getBoolMethodId = this->jvm->GetMethodID(this->boolClass, "booleanValue", "()Z");
    this->createBoolMethodId = this->jvm->GetMethodID(this->boolClass, "<init>", "(Z)V");

    this->getByteMethodId = this->jvm->GetMethodID(byteClass, "byteValue", "()B");
    this->createByteMethodId = this->jvm->GetMethodID(byteClass, "<init>", "(B)V");

    this->getIntMethodId = this->jvm->GetMethodID(intClass, "intValue", "()I");
    this->createIntMethodId = this->jvm->GetMethodID(intClass, "<init>", "(I)V");

    this->getLongMethodId = this->jvm->GetMethodID(this->longClass, "longValue", "()J");
    this->createLongMethodId = this->jvm->GetMethodID(this->longClass, "<init>", "(J)V");

    this->getShortMethodId = this->jvm->GetMethodID(this->shortClass, "shortValue", "()S");
    this->createShortMethodId = this->jvm->GetMethodID(this->shortClass, "<init>", "(S)V");

    this->getFloatMethodId = this->jvm->GetMethodID(this->floatClass, "floatValue", "()F");
    this->createFloatMethodId = this->jvm->GetMethodID(this->floatClass, "<init>", "(F)V");

    this->getDoubleMethodId = this->jvm->GetMethodID(doubleClass, "doubleValue", "()D");
    this->createDoubleMethodId = this->jvm->GetMethodID(doubleClass, "<init>", "(D)V");
}

jstring TypeUtils::toJavaString(const char *s)
{
    return this->jvm->NewStringUTF(s);
}

const char *TypeUtils::fromJavaString(jstring s)
{
    const char *tempStr = this->jvm->GetStringUTFChars(s, NULL);
    int tempLen = strlen(tempStr);
    char *cStr = (char *)malloc((tempLen + 1) * sizeof(char));
    strcpy(cStr, tempStr);
    this->jvm->ReleaseStringUTFChars(s, tempStr);
    return cStr;
}

jmethodID TypeUtils::getBoolMethod()
{
    return this->getBoolMethodId;
}

jmethodID TypeUtils::getByteMethod()
{
    return this->getByteMethodId;
}

jmethodID TypeUtils::getIntMethod()
{
    return this->getIntMethodId;
}

jmethodID TypeUtils::getLongMethod()
{
    return this->getLongMethodId;
}

jmethodID TypeUtils::getFloatMethod()
{
    return this->getFloatMethodId;
}

jmethodID TypeUtils::getDoubleMethod()
{
    return this->getDoubleMethodId;
}

jmethodID TypeUtils::getShortMethod()
{
    return this->getShortMethodId;
}

jmethodID TypeUtils::createBoolMethod()
{
    return this->createBoolMethodId;
}

jmethodID TypeUtils::createByteMethod()
{
    return this->createByteMethodId;
}

jmethodID TypeUtils::createIntMethod()
{
    return this->createIntMethodId;
}

jmethodID TypeUtils::createLongMethod()
{
    return this->createLongMethodId;
}

jmethodID TypeUtils::createFloatMethod()
{
    return this->createFloatMethodId;
}

jmethodID TypeUtils::createDoubleMethod()
{
    return this->createDoubleMethodId;
}

jmethodID TypeUtils::createShortMethod()
{
    return this->createShortMethodId;
}

/* Accessors for classes */
jclass TypeUtils::getIntClass()
{
    return this->intClass;
}

jclass TypeUtils::getLongClass()
{
    return this->longClass;
}

jclass TypeUtils::getFloatClass()
{
    return this->floatClass;
}

jclass TypeUtils::getDoubleClass()
{
    return this->doubleClass;
}

jclass TypeUtils::getByteClass()
{
    return this->byteClass;
}

jclass TypeUtils::getStringClass()
{
    return this->stringClass;
}

jclass TypeUtils::getBoolClass()
{
    return this->boolClass;
}

jclass TypeUtils::getShortClass()
{
    return this->shortClass;
}

jclass TypeUtils::getListClass()
{
    return this->listClass;
}

jclass TypeUtils::getMapClass()
{
    return this->mapClass;
}
