#include <jni.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
    extern record_list *getRequestRecords(session *session, request *request);
    extern record *getRequestRecord(session *session, request *request);
    extern void setRequestRecords(session *session, request *request, record_list *records);
    extern response *submitRequest(session *session, request *request);

    /* Response methods */
    extern bool isComplete(session *session, response *response);
    extern request *getResponseRequest(session *session, response *response);
    extern rejection_list *getResponseRejections(session *session, response *response);
    extern record_list *getResponseRecords(session *session, response *response);
    extern void setResponseRejections(session *session, response *response, rejection_list *rejections);
    extern void setResponseRecords(session *session, response *response, record_list *records);
    extern void setComplete(session *session, response *response, bool isComplete);

    /*Record Methods*/
    extern record_list *createRecordList(session *session);
    extern void addRecord(session *session, record_list *record_list, record *record);

    extern record *getRecordCopy(session *session, record *record);
    extern bool getRecordIsValid(session *session, record *record);

    extern string_list *getFieldIds(session *session, record *record);
    extern field_list *getFields(session *session, record *record);
    extern field *getField(session *session, record *record, const char *fieldId);
    extern bool hasField(session *session, record *record, const char *fieldId);

    extern string_list *getConditionIds(session *session, record *record);
    extern condition_list *getConditions(session *session, record *record);
    extern condition *getCondition(session *session, record *record, const char *conditionId);
    extern bool hasCondition(session *session, record *record, const char *conditionId);

    /*Rejection Methods*/
    extern rejection_list *createRejectionList(session *session);
    extern void addRejection(session *session, rejection_list *rejection_list, rejection *rejection);
    extern rejection *getRejectionCopy(session *session, rejection *rejection);
    extern record *getRejectionRecord(session *session, rejection *rejection);
    extern string_list *getRejectionReasons(session *session, rejection *rejection);
    extern void addRejectionReason(session *session, rejection *rejection, const char *reason);

    /*Field Methods*/
    extern const char *getFieldId(session *session, field *field);
    extern const char *getFieldType(session *session, field *field);
    extern bool getFieldIsValid(session *session, field *field);
    extern bool getFieldIsRequired(session *session, field *field);
    extern bool getFieldIsNull(session *session, field *field);

    /* Field Value Retrieval */
    extern val *getFieldVal(session *session, field *field);
    extern int getFieldIntVal(session *session, field *field);
    extern long getFieldLongVal(session *session, field *field);
    extern float getFieldFloatVal(session *session, field *field);
    extern double getFieldDoubleVal(session *session, field *field);
    extern signed char getFieldByteVal(session *session, field *field);
    extern const char *getFieldStringVal(session *session, field *field);
    extern bool getFieldBoolVal(session *session, field *field);
    extern short getFieldShortVal(session *session, field *field);
    extern val_list *getFieldListVal(session *session, field *field);

    /*Field Value Puts */
    extern void setFieldVal(session *session, field *field, val *value);
    extern void setFieldIntVal(session *session, field *field, int value);
    extern void setFieldLongVal(session *session, field *field, long value);
    extern void setFieldFloatVal(session *session, field *field, float value);
    extern void setFieldDoubleVal(session *session, field *field, double value);
    extern void setFieldByteVal(session *session, field *field, signed char value);
    extern void setFieldStringVal(session *session, field *field, const char *value);
    extern void setFieldBoolVal(session *session, field *field, bool value);
    extern void setFieldShortVal(session *session, field *field, short value);
    extern void setFieldListVal(session *session, field *field, val_list *value);

    /*Condition Methods*/
    extern const char *getConditionId(session *session, condition *condition);
    extern const char *getConditionType(session *session, condition *condition);
    extern const char *getConditionOperator(session *session, condition *condition);
    extern bool getConditionIsNull(session *session, condition *condition);

    /* Condition value retrieval */
    extern val *getConditionVal(session *session, condition *condition);
    extern int getConditionIntVal(session *session, condition *condition);
    extern long getConditionLongVal(session *session, condition *condition);
    extern float getConditionFloatVal(session *session, condition *condition);
    extern double getConditionDoubleVal(session *session, condition *condition);
    extern signed char getConditionByteVal(session *session, condition *condition);
    extern const char *getConditionStringVal(session *session, condition *condition);
    extern bool getConditionBoolVal(session *session, condition *condition);
    extern short getConditionShortVal(session *session, condition *condition);
    extern val_list *getConditionListVal(session *session, condition *condition);

    /* Condition value puts */
    extern void setConditionVal(session *session, condition *condition, val *value);
    extern void setConditionIntVal(session *session, condition *condition, int value);
    extern void setConditionLongVal(session *session, condition *condition, long value);
    extern void setConditionFloatVal(session *session, condition *condition, float value);
    extern void setConditionDoubleVal(session *session, condition *condition, double value);
    extern void setConditionByteVal(session *session, condition *condition, signed char value);
    extern void setConditionStringVal(session *session, condition *condition, const char *value);
    extern void setConditionBoolVal(session *session, condition *condition, bool value);
    extern void setConditionShortVal(session *session, condition *condition, short value);
    extern void setConditionListVal(session *session, condition *condition, val_list *value);

    /*List Utility Methods*/
    extern int getIntItem(session *session, val_list *list, int index);
    extern long getLongItem(session *session, val_list *list, int index);
    extern float getFloatItem(session *session, val_list *list, int index);
    extern double getDoubleItem(session *session, val_list *list, int index);
    extern signed char getByteItem(session *session, val_list *list, int index);
    extern const char *getStringItem(session *session, val_list *list, int index);
    extern bool getBoolItem(session *session, val_list *list, int index);
    extern short getShortItem(session *session, val_list *list, int index);
    extern list_item *getItem(session *session, val_list *list, int index);
    extern val_list *getListItem(session *session, val_list *list, int index);
    extern val_map *getMapItem(session *session, val_list *list, int index);
    extern val_list *createList(session *session);
    extern void addItem(session *session, val_list *list, list_item *item);
    extern void addIntItem(session *session, val_list *list, int val);
    extern void addLongItem(session *session, val_list *list, long val);
    extern void addFloatItem(session *session, val_list *list, float val);
    extern void addDoubleItem(session *session, val_list *list, double val);
    extern void addByteItem(session *session, val_list *list, signed char val);
    extern void addStringItem(session *session, val_list *list, const char *val);
    extern void addBoolItem(session *session, val_list *list, bool val);
    extern void addShortItem(session *session, val_list *list, short val);
    extern void addListItem(session *session, val_list *list, val_list *val);
    extern void addMapItem(session *session, val_list *list, val_map *map);

    /*Map Utility Methods*/
    extern val_map *createMap(session *session);
    extern int getSize(session *session, val_map *map);
    extern bool hasKey(session *session, val_map *map, const char *key);

    /*Map Value Retrieval Methods*/
    extern map_val *getVal(session *session, val_map *map, const char *key);
    extern jobject getObjectVal(session *session, val_map *map, const char *key);
    extern int getIntVal(session *session, val_map *map, const char *key);
    extern long getLongVal(session *session, val_map *map, const char *key);
    extern float getFloatVal(session *session, val_map *map, const char *key);
    extern double getDoubleVal(session *session, val_map *map, const char *key);
    extern signed char getByteVal(session *session, val_map *map, const char *key);
    extern const char *getStringVal(session *session, val_map *map, const char *key);
    extern bool getBoolVal(session *session, val_map *map, const char *key);
    extern short getShortVal(session *session, val_map *map, const char *key);
    extern val_list *getListVal(session *session, val_map *map, const char *key);
    extern val_map *getMapVal(session *session, val_map *map, const char *key);

    /*Insert or Update Methods*/
    extern void putVal(session *session, val_map *map, const char *key, map_val *val);
    extern void putObjectVal(session *session, val_map *map, const char *key, jobject val);
    extern void putIntVal(session *session, val_map *map, const char *key, int val);
    extern void putLongVal(session *session, val_map *map, const char *key, long val);
    extern void putFloatVal(session *session, val_map *map, const char *key, float val);
    extern void putDoubleVal(session *session, val_map *map, const char *key, double val);
    extern void putByteVal(session *session, val_map *map, const char *key, signed char val);
    extern void putStringVal(session *session, val_map *map, const char *key, const char *val);
    extern void putBoolVal(session *session, val_map *map, const char *key, bool val);
    extern void putShortVal(session *session, val_map *map, const char *key, short val);
    extern void putListVal(session *session, val_map *map, const char *key, val_list *val);
    extern void putMapVal(session *session, val_map *map, const char *key, val_map *val);

    /*Packet Methods*/
    extern void addPacketRecord(session *session, packet *packet, record *record);
    extern void setPacketRecords(session *session, packet *packet, record_list *records);
    extern void addPacketRecords(session *session, packet *packet, record_list *records);
    extern void setPacketRejections(session *session, packet *packet, rejection_list *rejections);
    extern void addPacketRejection(session *session, packet *packet, rejection *rejection);
    extern void addPacketRejections(session *session, packet *packet, rejection_list *rejections);
    extern record_list *getPacketRecords(session *session, packet *packet);
    extern rejection_list *getPacketRejections(session *session, packet *packet);

#ifdef __cplusplus
}
#endif
