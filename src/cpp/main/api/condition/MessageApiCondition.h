#ifndef _Included_MessageApiCondition
#define _Included_MessageApiCondition

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "MapUtils.h"
#include "ListUtils.h"
#include "FieldUtils.h"
#include "ConditionUtils.h"
#include "NativeConditionUtils.h"

//test commit

/**
 * This is the header for the MessageApiCondition class - this class is the native side facility
 * for doing condition comparison processing and communicating back with the java side. This class holds
 * four private vars - a pointer to the jvm where the call originated from, a pointer to the
 * condition class instance (jobject), a pointer to the field on which the comparison is being called,
 * and a pointer to the condition containing a value for comparison.
 * 
 * To use the MessageApiCondition natively, users can write any logic that can use the passed field
 * and passed condition to extract values and do arbitrary comparison. Returning a true boolean will
 * mean the condition passed, while returning a false value will mean the condition failed.
 * 
 * To the user of the MessageApiCondition library in the native side,
 * they will see the entire library as a single jlong. This jlong holds a pointer to this class,
 * making it easier for implementors to ignore most of the details of implementation.
 * @author Ryan Berkheimer
 */
class MessageApiCondition
{

public:
    /*Default constructor/destructors*/
    MessageApiCondition(JNIEnv* javaEnv, jobject jNativeCondition, jobject jField, jobject jCondition);
    ~MessageApiCondition();

    /*Utils Accessors*/
    FieldUtils *getFieldUtils();
    ConditionUtils *getConditionUtils();
    NativeConditionUtils *getNativeConditionUtils();
    TypeUtils *getTypeUtils();
    ListUtils *getListUtils();
    MapUtils *getMapUtils();

private :
    /*Global References*/
    JNIEnv *jvm;
    jobject nativeCondition;
    jobject field;
    jobject condition;
    
    FieldUtils *fieldUtils;
    ConditionUtils *conditionUtils;
    NativeConditionUtils *nativeConditionUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;
    MapUtils *mapUtils;

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
