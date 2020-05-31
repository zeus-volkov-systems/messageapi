#include "MapUtils.h"

/* Default Constructor */
MapUtils::MapUtils(JNIEnv *env, TypeUtils *typeUtils)
{
    this->loadGlobalRefs(env, typeUtils);
    this->loadMethodIds();
}

/* Default destructor */
MapUtils::~MapUtils()
{
    try
    {
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void MapUtils::loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils)
{
    this->jvm = env;
    this->typeUtils = typeUtils;
}

void MapUtils::loadMethodIds()
{
    jclass mapClass = JniUtils::getNamedClass(this->jvm, "java/util/Map");

    this->getSizeMethodId = this->jvm->GetMethodID(mapClass, "size", "()I");
    this->hasKeyMethodId = this->jvm->GetMethodID(mapClass, "containsKey", "(Ljava/lang/Object;)Z");
    this->getValueMethodId = this->jvm->GetMethodID(mapClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    this->putValueMethodId = this->jvm->GetMethodID(mapClass, "put", "(Ljava/lang/String;Ljava/lang/Object;)Ljava/lang/Object;");

    this->jvm->DeleteLocalRef(mapClass);

    this->createMapMethodId = this->jvm->GetMethodID(this->typeUtils->getMapClass(), "<init>", "()V");
}

jmethodID MapUtils::createMapMethod()
{
    return this->createMapMethodId;
}

jmethodID MapUtils::getSizeMethod()
{
    return this->getSizeMethodId;
}

jmethodID MapUtils::hasKeyMethod()
{
    return this->hasKeyMethodId;
}

jmethodID MapUtils::getValueMethod()
{
    return this->getValueMethodId;
}

jmethodID MapUtils::putValueMethod()
{
    return this->putValueMethodId;
}

struct val_map *MapUtils::createMap()
{
    jobject jMap = this->jvm->NewObject(this->typeUtils->getMapClass(), this->createMapMethod());
    struct val_map *valueMap = (struct val_map *)malloc(sizeof(struct val_map));
    valueMap->jmap = jMap;
    return valueMap;
}

int MapUtils::getSize(val_map *val_map)
{
    return (int)this->jvm->CallIntMethod(val_map->jmap, this->getSizeMethod());
}

bool MapUtils::hasKey(val_map *val_map, const char *key)
{
    return (bool)this->jvm->CallBooleanMethod(val_map->jmap, this->hasKeyMethod());
}

/*Map Value Retrieval Methods*/
struct map_val *MapUtils::getVal(struct val_map *map, const char *key)
{
    struct map_val *mapVal = (struct map_val *)malloc(sizeof(struct map_val));
    mapVal->jval = this->getObjectVal(map, key);
    return mapVal;
}

jobject MapUtils::getObjectVal(struct val_map *map, const char *key)
{
    jstring jkey = this->typeUtils->toJavaString(key);
    jobject objectVal = static_cast<jobject>(this->jvm->CallObjectMethod(map->jmap, this->getValueMethod(), jkey));
    this->jvm->DeleteLocalRef(jkey);
    return objectVal;
}

int MapUtils::getIntVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    int val = (int)this->jvm->CallIntMethod(jval, this->typeUtils->getIntMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

long MapUtils::getLongVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    long val = (long)this->jvm->CallLongMethod(jval, this->typeUtils->getLongMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

float MapUtils::getFloatVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    float val = (float)this->jvm->CallFloatMethod(jval, this->typeUtils->getFloatMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

double MapUtils::getDoubleVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    double val = (double)this->jvm->CallDoubleMethod(jval, this->typeUtils->getDoubleMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

signed char MapUtils::getByteVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    signed char val = (signed char)this->jvm->CallByteMethod(jval, this->typeUtils->getByteMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

const char *MapUtils::getStringVal(struct val_map *map, const char *key)
{
    jstring jString = static_cast<jstring>(this->jvm->CallObjectMethod(map->jmap, this->getValueMethod(), key));
    const char *val = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return val;
}

bool MapUtils::getBoolVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    bool val = (bool)this->jvm->CallBooleanMethod(jval, this->typeUtils->getBoolMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

short MapUtils::getShortVal(struct val_map *map, const char *key)
{
    jobject jval = this->getObjectVal(map, key);
    short val = (short)this->jvm->CallShortMethod(jval, this->typeUtils->getShortMethod());
    jvm->DeleteLocalRef(jval);
    return val;
}

struct val_list *MapUtils::getListVal(struct val_map *map, const char *key)
{
    jobject listItem = this->getObjectVal(map, key);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->jlist = listItem;
    return valueList;
}

struct val_map *MapUtils::getMapVal(struct val_map *map, const char *key)
{
    jobject jValMap = this->getObjectVal(map, key);
    struct val_map *valMap = (struct val_map *)malloc(sizeof(struct val_map));
    valMap->jmap = jValMap;
    return valMap;
}

/*Insert or Update Methods*/
void MapUtils::putVal(struct val_map *map, const char *key, struct map_val *val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, val->jval);
    this->jvm->DeleteLocalRef(jKey);
}

void MapUtils::putObjectVal(struct val_map *map, const char *key, jobject val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, val);
    this->jvm->DeleteLocalRef(jKey);
}

void MapUtils::putIntVal(struct val_map *map, const char *key, int val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putLongVal(struct val_map *map, const char *key, long val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putFloatVal(struct val_map *map, const char *key, float val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putDoubleVal(struct val_map *map, const char *key, double val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putByteVal(struct val_map *map, const char *key, signed char val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putStringVal(struct val_map *map, const char *key, const char *val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jstring jVal = this->typeUtils->toJavaString(val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putBoolVal(struct val_map *map, const char *key, bool val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putShortVal(struct val_map *map, const char *key, short val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    jobject jVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)val);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, jVal);
    this->jvm->DeleteLocalRef(jKey);
    this->jvm->DeleteLocalRef(jVal);
}

void MapUtils::putListVal(struct val_map *map, const char *key, struct val_list *val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, val->jlist);
    this->jvm->DeleteLocalRef(jKey);
}

void MapUtils::putMapVal(struct val_map *map, const char *key, struct val_map *val)
{
    jstring jKey = this->typeUtils->toJavaString(key);
    this->jvm->CallVoidMethod(map->jmap, this->putValueMethod(), jKey, val->jmap);
    this->jvm->DeleteLocalRef(jKey);
}
