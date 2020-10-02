#include <jni.h>
#include <stdbool.h>

#include "messageapi_structs.h"

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    /* Native Condition methods */
    val_map *getConstructor(jlong message);
    field *getField(jlong message);
    condition *getCondition(jlong message);

    /*Field Methods*/
    const char *getFieldId(jlong message, field *field);
    const char *getFieldType(jlong message, field *field);
    bool getFieldIsValid(jlong message, field *field);
    bool getFieldIsRequired(jlong message, field *field);
    bool getFieldIsNull(jlong message, field *field);

    val *getFieldVal(jlong message, field *field);
    int getFieldIntVal(jlong message, field *field);
    long getFieldLongVal(jlong message, field *field);
    float getFieldFloatVal(jlong message, field *field);
    double getFieldDoubleVal(jlong message, field *field);
    signed char getFieldByteVal(jlong message, field *field);
    const char *getFieldStringVal(jlong message, field *field);
    bool getFieldBoolVal(jlong message, field *field);
    short getFieldShortVal(jlong message, field *field);
    val_list *getFieldListVal(jlong message, field *field);
    val_map *getFieldMapVal(jlong message, field *field);

    /*Condition Methods*/
    const char *getConditionId(jlong message, condition *condition);
    const char *getConditionType(jlong message, condition *condition);
    const char *getConditionOperator(jlong message, condition *condition);
    bool getConditionIsNull(jlong message, condition *condition);

    val *getConditionVal(jlong message, condition *condition);
    int getConditionIntVal(jlong message, condition *condition);
    long getConditionLongVal(jlong message, condition *condition);
    float getConditionFloatVal(jlong message, condition *condition);
    double getConditionDoubleVal(jlong message, condition *condition);
    signed char getConditionByteVal(jlong message, condition *condition);
    const char *getConditionStringVal(jlong message, condition *condition);
    bool getConditionBoolVal(jlong message, condition *condition);
    short getConditionShortVal(jlong message, condition *condition);
    val_list *getConditionListVal(jlong message, condition *condition);
    val_map *getConditionMapVal(jlong message, condition *condition);

    /*List Utility Methods*/
    
    int getIntItem(jlong message, val_list *list, int index);
    long getLongItem(jlong message, val_list *list, int index);
    float getFloatItem(jlong message, val_list *list, int index);
    double getDoubleItem(jlong message, val_list *list, int index);
    signed char getByteItem(jlong message, val_list *list, int index);
    const char *getStringItem(jlong message, val_list *list, int index);
    bool getBoolItem(jlong message, val_list *list, int index);
    short getShortItem(jlong message, val_list *list, int index);
    list_item *getItem(jlong message, val_list *list, int index);
    val_list *getListItem(jlong message, val_list *list, int index);
    val_map *getMapItem(jlong message, val_list *list, int index);

    /*Map Utility Methods*/
    int getSize(jlong message, val_map *map);
    bool hasKey(jlong message, val_map *map, const char *key);

    /*Map Value Retrieval Methods*/
    map_val *getVal(jlong message, val_map *map, const char *key);
    jobject getObjectVal(jlong message, val_map *map, const char *key);
    int getIntVal(jlong message, val_map *map, const char *key);
    long getLongVal(jlong message, val_map *map, const char *key);
    float getFloatVal(jlong message, val_map *map, const char *key);
    double getDoubleVal(jlong message, val_map *map, const char *key);
    signed char getByteVal(jlong message, val_map *map, const char *key);
    const char *getStringVal(jlong message, val_map *map, const char *key);
    bool getBoolVal(jlong message, val_map *map, const char *key);
    short getShortVal(jlong message, val_map *map, const char *key);
    val_list *getListVal(jlong message, val_map *map, const char *key);
    val_map *getMapVal(jlong message, val_map *map, const char *key);


#ifdef __cplusplus
}
#endif
