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
    struct val_map *getConstructor(jlong message);
    struct record_list *getRecords(jlong message, const char *key);

    /*Record Methods*/
    struct record_list *createRecordList(jlong message);
    void addRecord(jlong message, struct record_list *record_list, struct record *record);

    struct record *getRecordCopy(jlong message, struct record *record);
    bool getRecordIsValid(jlong message, struct record *record);

    struct string_list *getFieldIds(jlong message, struct record *record);
    struct field_list *getFields(jlong message, struct record *record);
    struct field *getField(jlong message, struct record *record, const char *fieldId);
    bool hasField(jlong message, struct record *record, const char *fieldId);

    struct string_list *getConditionIds(jlong message, struct record *record);
    struct condition_list *getConditions(jlong message, struct record *record);
    struct condition *getCondition(jlong message, struct record *record, const char *conditionId);
    bool hasCondition(jlong message, struct record *record, const char *conditionId);

    /*Rejection Methods*/
    struct rejection_list *createRejectionList(jlong message);
    void addRejection(jlong message, struct rejection_list *rejection_list, struct rejection *rejection);
    struct rejection *getRejectionCopy(jlong message, struct rejection *rejection);
    struct record *getRejectionRecord(jlong message, struct rejection *rejection);
    struct string_list *getRejectionReasons(jlong message, struct rejection *rejection);
    void addRejectionReason(jlong message, struct rejection *rejection, const char *reason);

    /*Field Methods*/
    const char *getFieldId(jlong message, struct field *field);
    const char *getFieldType(jlong message, struct field *field);
    bool getFieldIsValid(jlong message, struct field *field);
    bool getFieldIsRequired(jlong message, struct field *field);
    bool getFieldIsNull(jlong message, struct field *field);

    struct val *getFieldVal(jlong message, struct field *field);
    int getFieldIntVal(jlong message, struct field *field);
    long getFieldLongVal(jlong message, struct field *field);
    float getFieldFloatVal(jlong message, struct field *field);
    double getFieldDoubleVal(jlong message, struct field *field);
    signed char getFieldByteVal(jlong message, struct field *field);
    const char *getFieldStringVal(jlong message, struct field *field);
    bool getFieldBoolVal(jlong message, struct field *field);
    short getFieldShortVal(jlong message, struct field *field);
    struct val_list *getFieldListVal(jlong message, struct field *field);
    struct val_map *getFieldMapVal(jlong message, struct field *field);

    void setFieldVal(jlong message, struct field *field, struct val *value);
    void setFieldIntVal(jlong message, struct field *field, int value);
    void setFieldLongVal(jlong message, struct field *field, long value);
    void setFieldFloatVal(jlong message, struct field *field, float value);
    void setFieldDoubleVal(jlong message, struct field *field, double value);
    void setFieldByteVal(jlong message, struct field *field, signed char value);
    void setFieldStringVal(jlong message, struct field *field, const char *value);
    void setFieldBoolVal(jlong message, struct field *field, bool value);
    void setFieldShortVal(jlong message, struct field *field, short value);
    void setFieldListVal(jlong message, struct field *field, struct val_list *value);
    void setFieldMapVal(jlong message, struct field *field, struct val_map *value);

    /*Condition Methods*/
    const char *getConditionId(jlong message, struct condition *condition);
    const char *getConditionType(jlong message, struct condition *condition);
    const char *getConditionOperator(jlong message, struct condition *condition);
    bool getConditionIsNull(jlong message, struct condition *condition);

    struct val *getConditionVal(jlong message, struct condition *condition);
    int getConditionIntVal(jlong message, struct condition *condition);
    long getConditionLongVal(jlong message, struct condition *condition);
    float getConditionFloatVal(jlong message, struct condition *condition);
    double getConditionDoubleVal(jlong message, struct condition *condition);
    signed char getConditionByteVal(jlong message, struct condition *condition);
    const char *getConditionStringVal(jlong message, struct condition *condition);
    bool getConditionBoolVal(jlong message, struct condition *condition);
    short getConditionShortVal(jlong message, struct condition *condition);
    struct val_list *getConditionListVal(jlong message, struct condition *condition);
    struct val_map *getConditionMapVal(jlong message, struct condition *condition);

    void setConditionVal(jlong message, struct condition *condition, struct val *value);
    void setConditionIntVal(jlong message, struct condition *condition, int value);
    void setConditionLongVal(jlong message, struct condition *condition, long value);
    void setConditionFloatVal(jlong message, struct condition *condition, float value);
    void setConditionDoubleVal(jlong message, struct condition *condition, double value);
    void setConditionByteVal(jlong message, struct condition *condition, signed char value);
    void setConditionStringVal(jlong message, struct condition *condition, const char *value);
    void setConditionBoolVal(jlong message, struct condition *condition, bool value);
    void setConditionShortVal(jlong message, struct condition *condition, short value);
    void setConditionListVal(jlong message, struct condition *condition, struct val_list *value);
    void setConditionMapVal(jlong message, struct condition *condition, struct val_map *value);

    /*List Utility Methods*/
    struct val_list *createList(jlong message);
    
    int getIntItem(jlong message, struct val_list *list, int index);
    long getLongItem(jlong message, struct val_list *list, int index);
    float getFloatItem(jlong message, struct val_list *list, int index);
    double getDoubleItem(jlong message, struct val_list *list, int index);
    signed char getByteItem(jlong message, struct val_list *list, int index);
    const char *getStringItem(jlong message, struct val_list *list, int index);
    bool getBoolItem(jlong message, struct val_list *list, int index);
    short getShortItem(jlong message, struct val_list *list, int index);
    struct list_item *getItem(jlong message, struct val_list *list, int index);
    struct val_list *getListItem(jlong message, struct val_list *list, int index);
    struct val_map *getMapItem(jlong message, struct val_list *list, int index);

    void addItem(jlong message, struct val_list *list, struct list_item *item);
    void addIntItem(jlong message, struct val_list *list, int val);
    void addLongItem(jlong message, struct val_list *list, long val);
    void addFloatItem(jlong message, struct val_list *list, float val);
    void addDoubleItem(jlong message, struct val_list *list, double val);
    void addByteItem(jlong message, struct val_list *list, signed char val);
    void addStringItem(jlong message, struct val_list *list, const char *val);
    void addBoolItem(jlong message, struct val_list *list, bool val);
    void addShortItem(jlong message, struct val_list *list, short val);
    void addListItem(jlong message, struct val_list *list, struct val_list *val);
    void addMapItem(jlong message, struct val_list *list, struct val_map *map);

    /*Map Utility Methods*/
    struct val_map *createMap(jlong message);
    int getSize(jlong message, struct val_map *map);
    bool hasKey(jlong message, struct val_map *map, const char *key);

    /*Map Value Retrieval Methods*/
    struct map_val *getVal(jlong message, struct val_map *map, const char *key);
    jobject getObjectVal(jlong message, struct val_map *map, const char *key);
    int getIntVal(jlong message, struct val_map *map, const char *key);
    long getLongVal(jlong message, struct val_map *map, const char *key);
    float getFloatVal(jlong message, struct val_map *map, const char *key);
    double getDoubleVal(jlong message, struct val_map *map, const char *key);
    signed char getByteVal(jlong message, struct val_map *map, const char *key);
    const char *getStringVal(jlong message, struct val_map *map, const char *key);
    bool getBoolVal(jlong message, struct val_map *map, const char *key);
    short getShortVal(jlong message, struct val_map *map, const char *key);
    struct val_list *getListVal(jlong message, struct val_map *map, const char *key);
    struct val_map *getMapVal(jlong message, struct val_map *map, const char *key);

    /*Insert or Update Methods*/
    void putVal(jlong message, struct val_map *map, const char *key, struct map_val *val);
    void putObjectVal(jlong message, struct val_map *map, const char *key, jobject val);
    void putIntVal(jlong message, struct val_map *map, const char *key, int val);
    void putLongVal(jlong message, struct val_map *map, const char *key, long val);
    void putFloatVal(jlong message, struct val_map *map, const char *key, float val);
    void putDoubleVal(jlong message, struct val_map *map, const char *key, double val);
    void putByteVal(jlong message, struct val_map *map, const char *key, signed char val);
    void putStringVal(jlong message, struct val_map *map, const char *key, const char *val);
    void putBoolVal(jlong message, struct val_map *map, const char *key, bool val);
    void putShortVal(jlong message, struct val_map *map, const char *key, short val);
    void putListVal(jlong message, struct val_map *map, const char *key, struct val_list *val);
    void putMapVal(jlong message, struct val_map *map, const char *key, struct val_map *val);

    /*Packet Methods*/
    void addPacketRecord(jlong message, struct packet *packet, struct record *record);
    void setPacketRecords(jlong message, struct packet *packet, struct record_list *records);
    void addPacketRecords(jlong message, struct packet *packet, struct record_list *records);
    void setPacketRejections(jlong message, struct packet *packet, struct rejection_list *rejections);
    void addPacketRejection(jlong message, struct packet *packet, struct rejection *rejection);
    void addPacketRejections(jlong message, struct packet *packet, struct rejection_list *rejections);
    struct record_list *getPacketRecords(jlong message, struct packet *packet);
    struct rejection_list *getPacketRejections(jlong message, struct packet *packet);

#ifdef __cplusplus
}
#endif
