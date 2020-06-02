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

    /* Transformation methods */
    val_map *getConstructor(jlong message);
    record_list *getRecords(jlong message, const char *key);

    /*Record Methods*/
    record_list *createRecordList(jlong message);
    void addRecord(jlong message, record_list *record_list, record *record);

    record *getRecordCopy(jlong message, record *record);
    bool getRecordIsValid(jlong message, record *record);

    string_list *getFieldIds(jlong message, record *record);
    field_list *getFields(jlong message, record *record);
    field *getField(jlong message, record *record, const char *fieldId);
    bool hasField(jlong message, record *record, const char *fieldId);

    string_list *getConditionIds(jlong message, record *record);
    condition_list *getConditions(jlong message, record *record);
    condition *getCondition(jlong message, record *record, const char *conditionId);
    bool hasCondition(jlong message, record *record, const char *conditionId);

    /*Rejection Methods*/
    rejection_list *createRejectionList(jlong message);
    void addRejection(jlong message, rejection_list *rejection_list, rejection *rejection);
    rejection *getRejectionCopy(jlong message, rejection *rejection);
    record *getRejectionRecord(jlong message, rejection *rejection);
    string_list *getRejectionReasons(jlong message, rejection *rejection);
    void addRejectionReason(jlong message, rejection *rejection, const char *reason);

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

    void setFieldVal(jlong message, field *field, val *value);
    void setFieldIntVal(jlong message, field *field, int value);
    void setFieldLongVal(jlong message, field *field, long value);
    void setFieldFloatVal(jlong message, field *field, float value);
    void setFieldDoubleVal(jlong message, field *field, double value);
    void setFieldByteVal(jlong message, field *field, signed char value);
    void setFieldStringVal(jlong message, field *field, const char *value);
    void setFieldBoolVal(jlong message, field *field, bool value);
    void setFieldShortVal(jlong message, field *field, short value);
    void setFieldListVal(jlong message, field *field, val_list *value);
    void setFieldMapVal(jlong message, field *field, val_map *value);

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

    void setConditionVal(jlong message, condition *condition, val *value);
    void setConditionIntVal(jlong message, condition *condition, int value);
    void setConditionLongVal(jlong message, condition *condition, long value);
    void setConditionFloatVal(jlong message, condition *condition, float value);
    void setConditionDoubleVal(jlong message, condition *condition, double value);
    void setConditionByteVal(jlong message, condition *condition, signed char value);
    void setConditionStringVal(jlong message, condition *condition, const char *value);
    void setConditionBoolVal(jlong message, condition *condition, bool value);
    void setConditionShortVal(jlong message, condition *condition, short value);
    void setConditionListVal(jlong message, condition *condition, val_list *value);
    void setConditionMapVal(jlong message, condition *condition, val_map *value);

    /*List Utility Methods*/
    val_list *createList(jlong message);
    
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

    void addItem(jlong message, val_list *list, list_item *item);
    void addIntItem(jlong message, val_list *list, int val);
    void addLongItem(jlong message, val_list *list, long val);
    void addFloatItem(jlong message, val_list *list, float val);
    void addDoubleItem(jlong message, val_list *list, double val);
    void addByteItem(jlong message, val_list *list, signed char val);
    void addStringItem(jlong message, val_list *list, const char *val);
    void addBoolItem(jlong message, val_list *list, bool val);
    void addShortItem(jlong message, val_list *list, short val);
    void addListItem(jlong message, val_list *list, val_list *val);
    void addMapItem(jlong message, val_list *list, val_map *map);

    /*Map Utility Methods*/
    val_map *createMap(jlong message);
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

    /*Insert or Update Methods*/
    void putVal(jlong message, val_map *map, const char *key, map_val *val);
    void putObjectVal(jlong message, val_map *map, const char *key, jobject val);
    void putIntVal(jlong message, val_map *map, const char *key, int val);
    void putLongVal(jlong message, val_map *map, const char *key, long val);
    void putFloatVal(jlong message, val_map *map, const char *key, float val);
    void putDoubleVal(jlong message, val_map *map, const char *key, double val);
    void putByteVal(jlong message, val_map *map, const char *key, signed char val);
    void putStringVal(jlong message, val_map *map, const char *key, const char *val);
    void putBoolVal(jlong message, val_map *map, const char *key, bool val);
    void putShortVal(jlong message, val_map *map, const char *key, short val);
    void putListVal(jlong message, val_map *map, const char *key, val_list *val);
    void putMapVal(jlong message, val_map *map, const char *key, val_map *val);

    /*Packet Methods*/
    void addPacketRecord(jlong message, packet *packet, record *record);
    void setPacketRecords(jlong message, packet *packet, record_list *records);
    void addPacketRecords(jlong message, packet *packet, record_list *records);
    void setPacketRejections(jlong message, packet *packet, rejection_list *rejections);
    void addPacketRejection(jlong message, packet *packet, rejection *rejection);
    void addPacketRejections(jlong message, packet *packet, rejection_list *rejections);
    record_list *getPacketRecords(jlong message, packet *packet);
    rejection_list *getPacketRejections(jlong message, packet *packet);

#ifdef __cplusplus
}
#endif
