
#ifndef _RECORDUTILS_H
#define _RECORDUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "ListUtils.h"
#include "TypeUtils.h"

/**
 * This is the header for the RecordUtils class. 
 * A record contains fields and conditions.
 */
class RecordUtils
{

public:
    /*Default constructor/destructors*/
    
    RecordUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils);
    ~RecordUtils();

    /*Record Methods*/

    struct record_list *createRecordList();
    void addRecord(struct record_list *record_list, struct record *record);
    struct record *getRecord(struct record_list *record_list, int index);

    struct record *getCopy(struct record *record);
    bool isValid(struct record *record);
    void setValid(struct record *record, bool isValid);
    
    bool hasField(struct record *record, const char *fieldId);
    struct string_list *getFieldIds(struct record *record);
    struct field_list *getFields(struct record *record);
    struct field *getField(struct record *record, const char *fieldId);

    bool hasCondition(struct record *record, const char *conditionId);
    struct string_list *getConditionIds(struct record *record);
    struct condition_list *getConditions(struct record *record);
    struct condition *getCondition(struct record *record, const char *conditionId);

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;
    TypeUtils *typeUtils;

    /*Record Methods*/
    jmethodID isValidMethodId;
    jmethodID setValidMethodId;
    jmethodID getCopyMethodId;
    jmethodID getFieldIdsMethodId;
    jmethodID getFieldsMethodId;
    jmethodID getFieldMethodId;
    jmethodID hasFieldMethodId;
    jmethodID getConditionIdsMethodId;
    jmethodID getConditionsMethodId;
    jmethodID hasConditionMethodId;
    jmethodID getConditionMethodId;

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
