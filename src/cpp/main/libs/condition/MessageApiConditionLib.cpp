#include "MessageApiConditionLib.h"
#include "MessageApiCondition.h"
#include "gov_noaa_messageapi_conditions_NativeCondition.h"

/**
 * Creates a C++ object and returns a pointer to it cast as a long. This allows the NativeCondition method
 * to hold onto it and manipulate it during the process method while preventing potential conflicts with
 * other threads or conditions using the same native library. This is used inside the Java process method.
 * The Native process method should be implemented in a separate User class wrapper.
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_conditions_NativeCondition_create(JNIEnv* env, jobject nativeCondition, jobject field, jobject condition)
{
    return reinterpret_cast<jlong>(new MessageApiCondition(env, nativeCondition, field, condition));
}

/**
 * Deletes the C++ pointer (calls C++ destructor)) that references the object created during condition construction.
 * This call is made automatically by the Java process method after native processing has completed.
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_conditions_NativeCondition_release(JNIEnv* env, jobject nativeCondition, jlong conditionLib)
{
    delete reinterpret_cast<MessageApiCondition *>(conditionLib);
}

extern "C"
{

    val_map *getConstructor(jlong message)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getNativeConditionUtils()->getConstructor();
    }

    field *getField(jlong message)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getNativeConditionUtils()->getField();
    }

    condition *getCondition(jlong message)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getNativeConditionUtils()->getCondition();
    }

    /*Field Methods*/

    const char *getFieldId(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getId(field);
    }

    const char *getFieldType(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getType(field);
    }

    bool getFieldIsValid(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->isValid(field);
    }

    bool getFieldIsRequired(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->isRequired(field);
    }

    bool getFieldIsNull(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->isNull(field);
    }

    val *getFieldVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getVal(field);
    }

    int getFieldIntVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getIntVal(field);
    }

    long getFieldLongVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getLongVal(field);
    }

    float getFieldFloatVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getFloatVal(field);
    }

    double getFieldDoubleVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getDoubleVal(field);
    }

    signed char getFieldByteVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getByteVal(field);
    }

    const char *getFieldStringVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getStringVal(field);
    }

    bool getFieldBoolVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getBoolVal(field);
    }

    short getFieldShortVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getShortVal(field);
    }

    val_list *getFieldListVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getListVal(field);
    }

    val_map *getFieldMapVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getFieldUtils()->getMapVal(field);
    }

    /*Condition Methods*/

    const char *getConditionId(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getId(condition);
    }

    const char *getConditionType(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getType(condition);
    }

    const char *getConditionOperator(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getOperator(condition);
    }

    bool getConditionIsNull(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->isNull(condition);
    }

    val *getConditionVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getVal(condition);
    }
    
    int getConditionIntVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getIntVal(condition);
    }

    long getConditionLongVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getLongVal(condition);
    }

    float getConditionFloatVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getFloatVal(condition);
    }

    double getConditionDoubleVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getDoubleVal(condition);
    }

    signed char getConditionByteVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getByteVal(condition);
    }

    const char *getConditionStringVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getStringVal(condition);
    }

    bool getConditionBoolVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getBoolVal(condition);
    }

    short getConditionShortVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getShortVal(condition);
    }

    val_list *getConditionListVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getListVal(condition);
    }

    val_map *getConditionMapVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getConditionUtils()->getMapVal(condition);
    }

    /*List Utility Methods*/

    list_item *getItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getItem(list, index);
    }

    val_list *getListItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getListItem(list, index);
    }

    int getIntItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getIntItem(list, index);
    }

    long getLongItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getLongItem(list, index);
    }

    float getFloatItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getFloatItem(list, index);
    }

    double getDoubleItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getDoubleItem(list, index);
    }

    signed char getByteItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getByteItem(list, index);
    }

    const char *getStringItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getStringItem(list, index);
    }

    bool getBoolItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getBoolItem(list, index);
    }

    short getShortItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getListUtils()->getShortItem(list, index);
    }

    /*Map Utils*/

    /*Map Utility Methods*/
    int getSize(jlong message, val_map *map)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getSize(map);
    }

    bool hasKey(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->hasKey(map, key);
    }

    /*Map Value Retrieval Methods*/
    map_val *getVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getVal(map, key);
    }

    jobject getObjectVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getObjectVal(map, key);
    }

    int getIntVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getIntVal(map, key);
    }

    long getLongVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getLongVal(map, key);
    }

    float getFloatVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getFloatVal(map, key);
    }

    double getDoubleVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getDoubleVal(map, key);
    }

    signed char getByteVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getByteVal(map, key);
    }

    const char *getStringVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getStringVal(map, key);
    }

    bool getBoolVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getBoolVal(map, key);
    }

    short getShortVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getShortVal(map, key);
    }

    val_list *getListVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getListVal(map, key);
    }

    val_map *getMapVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiCondition *>(message)->getMapUtils()->getMapVal(map, key);
    }
}