
#ifndef _CONDITIONUTILS_H
#define _CONDITIONUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"

/**
 * This is the header for the ConditionUtils class. 
 * A record contains fields and conditions.
 */
class ConditionUtils
{

public:
    /*Default constructor/destructors*/
    ConditionUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils);
    ~ConditionUtils();

    /*API Methods*/
    const char *getId(struct condition *condition);
    const char *getType(struct condition *condition);
    const char *getOperator(struct condition *condition);
    bool isNull(struct condition *condition);
    struct val *getVal(struct condition *condition);
    int getIntVal(struct condition *condition);
    long getLongVal(struct condition *condition);
    float getFloatVal(struct condition *condition);
    double getDoubleVal(struct condition *condition);
    signed char getByteVal(struct condition *condition);
    const char *getStringVal(struct condition *condition);
    bool getBoolVal(struct condition *condition);
    short getShortVal(struct condition *condition);
    struct val_list *getListVal(struct condition *condition);
    void setVal(struct condition *condition, struct val *value);
    void setIntVal(struct condition *condition, int value);
    void setLongVal(struct condition *condition, long value);
    void setFloatVal(struct condition *condition, float value);
    void setDoubleVal(struct condition *condition, double value);
    void setByteVal(struct condition *condition, signed char value);
    void setStringVal(struct condition *condition, const char *value);
    void setBoolVal(struct condition *condition, bool value);
    void setShortVal(struct condition *condition, short value);
    void setListVal(struct condition *condition, struct val_list *value);

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;
    TypeUtils *typeUtils;

    /*Condition Methods*/
    jmethodID getIdMethodId;
    jmethodID getTypeMethodId;
    jmethodID getOperatorMethodId;
    jmethodID getValueMethodId;
    jmethodID setValueMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils, ListUtils *listUtils);

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
