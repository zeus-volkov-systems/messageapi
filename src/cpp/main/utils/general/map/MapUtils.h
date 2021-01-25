#ifndef _MAPUTILS_H
#define _MAPUTILS_H

#include <jni.h>
#include "messageapi_structs.h"

#ifdef __cplusplus

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "JniUtils.h"
#include "TypeUtils.h"
#include "ListUtils.h"

/**
 * This is the header for the MapUtils object class. MapUtils contains a set of methods used for manipulation of Java Maps
 * in C++ or C code. MapUtils is a class to be instantiated so that it remains thread safe for implementors.
 */
class MapUtils
{

public:
    /* Default constructor for ListUtils */
    MapUtils(JNIEnv *env, TypeUtils *typeUtils);

    /* Default destructor for ListUtils */
    ~MapUtils();

    /* Utility methods */
    struct val_map *createMap();
    int getSize(struct val_map *map);
    bool hasKey(struct val_map *map, const char *key);

    /*Map Value Retrieval Methods*/
    struct map_val *getVal(struct val_map *map, const char *key);
    jobject getObjectVal(struct val_map *map, const char *key);
    int getIntVal(struct val_map *map, const char *key);
    long getLongVal(struct val_map *map, const char *key);
    float getFloatVal(struct val_map *map, const char *key);
    double getDoubleVal(struct val_map *map, const char *key);
    signed char getByteVal(struct val_map *map, const char *key);
    const char *getStringVal(struct val_map *map, const char *key);
    bool getBoolVal(struct val_map *map, const char *key);
    short getShortVal(struct val_map *map, const char *key);
    struct val_list *getListVal(struct val_map *map, const char *key);
    struct val_map *getMapVal(struct val_map *map, const char *key);

    /*Insert or Update Methods*/
    void putVal(struct val_map *map, const char *key, struct map_val *val);
    void putObjectVal(struct val_map *map, const char *key, jobject val);
    void putIntVal(struct val_map *map, const char *key, int val);
    void putLongVal(struct val_map *map, const char *key, long val);
    void putFloatVal(struct val_map *map, const char *key, float val);
    void putDoubleVal(struct val_map *map, const char *key, double val);
    void putByteVal(struct val_map *map, const char *key, signed char val);
    void putStringVal(struct val_map *map, const char *key, const char *val);
    void putBoolVal(struct val_map *map, const char *key, bool val);
    void putShortVal(struct val_map *map, const char *key, short val);
    void putListVal(struct val_map *map, const char *key, struct val_list *val);
    void putMapVal(struct val_map *map, const char *key, struct val_map *val);

    jmethodID createMapMethod();
    jmethodID getSizeMethod();
    jmethodID hasKeyMethod();
    jmethodID getValueMethod();
    jmethodID putValueMethod();


private:
    JNIEnv *jvm;
    TypeUtils *typeUtils;
    ListUtils *listUtils;
    std::vector<struct val_map*> valueMapVector;

    jmethodID createMapMethodId;
    jmethodID getSizeMethodId;
    jmethodID hasKeyMethodId;
    jmethodID getValueMethodId;
    jmethodID putValueMethodId;

    /* Initialization Methods */
    void loadGlobalRefs(JNIEnv *env, TypeUtils *TypeUtils);
    void loadMethodIds();

    /* Destructor Methods*/
    void freeRefs();

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
