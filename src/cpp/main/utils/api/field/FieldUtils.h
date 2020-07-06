#ifndef _FIELDUTILS_H
#define _FIELDUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "TypeUtils.h"
#include "ListUtils.h"
#include "MapUtils.h"

/**
 * This is the header for the FieldUtils class. 
 * A record contains fields and conditions.
 */
class FieldUtils
{

public:
    /*Default constructor/destructors*/
    FieldUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils, MapUtils *mapUtils);
    ~FieldUtils();

    /*Field Methods*/
    const char *getId(struct field *field);
    const char *getType(struct field *field);
    bool isValid(struct field *field);
    bool isRequired(struct field *field);
    bool isNull(struct field *field);
    
    struct val *getVal(struct field *field);
    int getIntVal(struct field *field);
    long getLongVal(struct field *field);
    float getFloatVal(struct field *field);
    double getDoubleVal(struct field *field);
    signed char getByteVal(struct field *field);
    const char *getStringVal(struct field *field);
    bool getBoolVal(struct field *field);
    short getShortVal(struct field *field);
    struct val_list *getListVal(struct field *field);
    struct val_map *getMapVal(struct field *field);

    void setVal(struct field *field, struct val *value);
    void setIntVal(struct field *field, int value);
    void setLongVal(struct field *field, long value);
    void setFloatVal(struct field *field, float value);
    void setDoubleVal(struct field *field, double value);
    void setByteVal(struct field *field, signed char value);
    void setStringVal(struct field *field, const char *value);
    void setBoolVal(struct field *field, bool value);
    void setShortVal(struct field *field, short value);
    void setListVal(struct field *field, struct val_list *value);
    void setMapVal(struct field *field, struct val_map *value);

private:

    /*Vars*/
    JNIEnv *jvm;
    TypeUtils *typeUtils;
    ListUtils *listUtils;
    MapUtils *mapUtils;

    /*Field Methods*/
    jmethodID getIdMethodId;
    jmethodID getTypeMethodId;
    jmethodID getValueMethodId;
    jmethodID isValidMethodId;
    jmethodID isRequiredMethodId;
    jmethodID setValueMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils, ListUtils *listUtils, MapUtils *mapUtils);

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
