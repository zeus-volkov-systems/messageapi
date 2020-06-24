#include <jni.h>
#include <stdbool.h>

#include "messageapi_structs.h"

#include "JniUtils.h"
#include "MessageApiSession.h"
/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    /* Session methods */
    extern session *createSession(const char* specPath);
    extern void releaseSession(session *session);
    extern request *createRequest(session *session);

    /* Request methods */
    extern record *createRequestRecord(session *session, request *request);
    extern request *getRequestCopy(session *session, request *request);
    extern request *getRequestCopyComponents(session *session, request *request, val_list *copy_components);
    extern const char *getRequestType(session *session, request *request);
    record_list *getRequestRecords(session *session, request *request);
    record *getRequestRecord(session *session, request *request);
    void setRequestRecords(session *session, request *request, record_list *records);
    response *submitRequest(session *session, request *request);

    /* Response methods */
    bool isComplete(session *session, response *response);
    request *getResponseRequest(session *session, response *response);
    rejection_list *getResponseRejections(session *session, response *response);
    record_list *getResponseRecords(session *session, response *response);
    void setResponseRejections(session *session, response *response, rejection_list *rejections);
    void setResponseRecords(session *session, response *response, record_list *records);
    void setComplete(session *session, response *response, bool isComplete);

    /*Record Methods*/
    record_list *createRecordList(session *session);
    void addRecord(session *session, record_list *record_list, record *record);

    record *getRecordCopy(session *session, record *record);
    bool getRecordIsValid(session *session, record *record);

    string_list *getFieldIds(session *session, record *record);
    field_list *getFields(session *session, record *record);
    field *getField(session *session, record *record, const char *fieldId);
    bool hasField(session *session, record *record, const char *fieldId);

    string_list *getConditionIds(session *session, record *record);
    condition_list *getConditions(session *session, record *record);
    condition *getCondition(session *session, record *record, const char *conditionId);
    bool hasCondition(session *session, record *record, const char *conditionId);

    /*Rejection Methods*/
    rejection_list *createRejectionList(session *session);
    void addRejection(session *session, rejection_list *rejection_list, rejection *rejection);
    rejection *getRejectionCopy(session *session, rejection *rejection);
    record *getRejectionRecord(session *session, rejection *rejection);
    string_list *getRejectionReasons(session *session, rejection *rejection);
    void addRejectionReason(session *session, rejection *rejection, const char *reason);

    /*Field Methods*/
    const char *getFieldId(session *session, field *field);
    const char *getFieldType(session *session, field *field);
    bool getFieldIsValid(session *session, field *field);
    bool getFieldIsRequired(session *session, field *field);
    bool getFieldIsNull(session *session, field *field);

    /* Field Value Retrieval */
    val *getFieldVal(session *session, field *field);
    int getFieldIntVal(session *session, field *field);
    long getFieldLongVal(session *session, field *field);
    float getFieldFloatVal(session *session, field *field);
    double getFieldDoubleVal(session *session, field *field);
    signed char getFieldByteVal(session *session, field *field);
    const char *getFieldStringVal(session *session, field *field);
    bool getFieldBoolVal(session *session, field *field);
    short getFieldShortVal(session *session, field *field);
    val_list *getFieldListVal(session *session, field *field);

    /*Field Value Puts */
    void setFieldVal(session *session, field *field, val *value);
    void setFieldIntVal(session *session, field *field, int value);
    void setFieldLongVal(session *session, field *field, long value);
    void setFieldFloatVal(session *session, field *field, float value);
    void setFieldDoubleVal(session *session, field *field, double value);
    void setFieldByteVal(session *session, field *field, signed char value);
    void setFieldStringVal(session *session, field *field, const char *value);
    void setFieldBoolVal(session *session, field *field, bool value);
    void setFieldShortVal(session *session, field *field, short value);
    void setFieldListVal(session *session, field *field, val_list *value);

    /*Condition Methods*/
    const char *getConditionId(session *session, condition *condition);
    const char *getConditionType(session *session, condition *condition);
    const char *getConditionOperator(session *session, condition *condition);
    bool getConditionIsNull(session *session, condition *condition);

    /* Condition value retrieval */
    val *getConditionVal(session *session, condition *condition);
    int getConditionIntVal(session *session, condition *condition);
    long getConditionLongVal(session *session, condition *condition);
    float getConditionFloatVal(session *session, condition *condition);
    double getConditionDoubleVal(session *session, condition *condition);
    signed char getConditionByteVal(session *session, condition *condition);
    const char *getConditionStringVal(session *session, condition *condition);
    bool getConditionBoolVal(session *session, condition *condition);
    short getConditionShortVal(session *session, condition *condition);
    val_list *getConditionListVal(session *session, condition *condition);

    /* Condition value puts */
    void setConditionVal(session *session, condition *condition, val *value);
    void setConditionIntVal(session *session, condition *condition, int value);
    void setConditionLongVal(session *session, condition *condition, long value);
    void setConditionFloatVal(session *session, condition *condition, float value);
    void setConditionDoubleVal(session *session, condition *condition, double value);
    void setConditionByteVal(session *session, condition *condition, signed char value);
    void setConditionStringVal(session *session, condition *condition, const char *value);
    void setConditionBoolVal(session *session, condition *condition, bool value);
    void setConditionShortVal(session *session, condition *condition, short value);
    void setConditionListVal(session *session, condition *condition, val_list *value);

    /*List Utility Methods*/
    int getIntItem(session *session, val_list *list, int index);
    long getLongItem(session *session, val_list *list, int index);
    float getFloatItem(session *session, val_list *list, int index);
    double getDoubleItem(session *session, val_list *list, int index);
    signed char getByteItem(session *session, val_list *list, int index);
    const char *getStringItem(session *session, val_list *list, int index);
    bool getBoolItem(session *session, val_list *list, int index);
    short getShortItem(session *session, val_list *list, int index);
    list_item *getItem(session *session, val_list *list, int index);
    val_list *getListItem(session *session, val_list *list, int index);
    val_map *getMapItem(session *session, val_list *list, int index);
    val_list *createList(session *session);
    void addItem(session *session, val_list *list, list_item *item);
    void addIntItem(session *session, val_list *list, int val);
    void addLongItem(session *session, val_list *list, long val);
    void addFloatItem(session *session, val_list *list, float val);
    void addDoubleItem(session *session, val_list *list, double val);
    void addByteItem(session *session, val_list *list, signed char val);
    void addStringItem(session *session, val_list *list, const char *val);
    void addBoolItem(session *session, val_list *list, bool val);
    void addShortItem(session *session, val_list *list, short val);
    void addListItem(session *session, val_list *list, val_list *val);
    void addMapItem(session *session, val_list *list, val_map *map);

    /*Map Utility Methods*/
    val_map *createMap(session *session);
    int getSize(session *session, val_map *map);
    bool hasKey(session *session, val_map *map, const char *key);

    /*Map Value Retrieval Methods*/
    map_val *getVal(session *session, val_map *map, const char *key);
    jobject getObjectVal(session *session, val_map *map, const char *key);
    int getIntVal(session *session, val_map *map, const char *key);
    long getLongVal(session *session, val_map *map, const char *key);
    float getFloatVal(session *session, val_map *map, const char *key);
    double getDoubleVal(session *session, val_map *map, const char *key);
    signed char getByteVal(session *session, val_map *map, const char *key);
    const char *getStringVal(session *session, val_map *map, const char *key);
    bool getBoolVal(session *session, val_map *map, const char *key);
    short getShortVal(session *session, val_map *map, const char *key);
    val_list *getListVal(session *session, val_map *map, const char *key);
    val_map *getMapVal(session *session, val_map *map, const char *key);

    /*Insert or Update Methods*/
    void putVal(session *session, val_map *map, const char *key, map_val *val);
    void putObjectVal(session *session, val_map *map, const char *key, jobject val);
    void putIntVal(session *session, val_map *map, const char *key, int val);
    void putLongVal(session *session, val_map *map, const char *key, long val);
    void putFloatVal(session *session, val_map *map, const char *key, float val);
    void putDoubleVal(session *session, val_map *map, const char *key, double val);
    void putByteVal(session *session, val_map *map, const char *key, signed char val);
    void putStringVal(session *session, val_map *map, const char *key, const char *val);
    void putBoolVal(session *session, val_map *map, const char *key, bool val);
    void putShortVal(session *session, val_map *map, const char *key, short val);
    void putListVal(session *session, val_map *map, const char *key, val_list *val);
    void putMapVal(session *session, val_map *map, const char *key, val_map *val);

    /*Packet Methods*/
    void addPacketRecord(session *session, packet *packet, record *record);
    void setPacketRecords(session *session, packet *packet, record_list *records);
    void addPacketRecords(session *session, packet *packet, record_list *records);
    void setPacketRejections(session *session, packet *packet, rejection_list *rejections);
    void addPacketRejection(session *session, packet *packet, rejection *rejection);
    void addPacketRejections(session *session, packet *packet, rejection_list *rejections);
    record_list *getPacketRecords(session *session, packet *packet);
    rejection_list *getPacketRejections(session *session, packet *packet);

#ifdef __cplusplus
}
#endif
