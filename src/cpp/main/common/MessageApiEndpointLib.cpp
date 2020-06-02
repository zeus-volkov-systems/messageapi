#include "MessageApiEndpointLib.h"
#include "MessageApiEndpoint.h"
#include "gov_noaa_messageapi_endpoints_NativeEndpoint.h"

/**
 * Creates a C++ object and returns a pointer to it cast as a long. This allows the NativeEndpoint method
 * to hold onto it and manipulate it during the process method while preventing potential conflicts with
 * other threads or endpoints using the same native library. This is used inside the Java process method.
 * The Native process method should be implemented in a separate User class wrapper.
 */
JNIEXPORT jlong JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_create(JNIEnv* env, jobject endpoint, jobject record)
{
    return reinterpret_cast<jlong>(new MessageApiEndpoint(env, endpoint, record));
}

/**
 * Deletes the C++ pointer (calls C++ destructor)) that references the object created during endpoint construction.
 * This call is made automatically by the Java process method after native processing has completed.
 */
JNIEXPORT void JNICALL Java_gov_noaa_messageapi_endpoints_NativeEndpoint_release(JNIEnv* env, jobject task, jlong messageapilib)
{
    delete reinterpret_cast<MessageApiEndpoint *>(messageapilib);
}

extern "C"
{

    record *getStateContainer(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->getStateContainer();
    }

    field_list *getDefaultFields(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->getDefaultFields();
    }

    val_map *getConstructor(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->getConstructor();
    }

    packet *createPacket(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->createPacket();
    }

    record *createRecord(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->createRecord();
    }

    rejection *createRejection(jlong message, record *record, const char *reason)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getEndpointUtils()->createRejection(record, reason);
    }

    record_list *getRecords(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getProtocolRecordUtils()->getRecords("getRecords");
    }

    record_list *getRecordsByCollection(jlong message, const char *collectionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getProtocolRecordUtils()->getRecords("getRecordsByCollection", collectionId);
    }

    record_list *getRecordsByTransformation(jlong message, const char *transformationId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getProtocolRecordUtils()->getRecords("getRecordsByTransformation", transformationId);
    }

    record_list *getRecordsByUUID(jlong message, const char *uuid)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getProtocolRecordUtils()->getRecords("getRecordsByUUID", uuid);
    }

    record_list *getRecordsByClassifier(jlong message, const char *classifierKey, const char *classifierValue)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getProtocolRecordUtils()->getRecords("getRecordsByClassifier", classifierKey, classifierValue);
    }

    record_list *createRecordList(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->createRecordList();
    }

    void addRecord(jlong message, record_list *record_list, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->addRecord(record_list, record);
    }

    record *getRecord(jlong message, record_list *recordList, int recordIndex)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getRecord(recordList, recordIndex);
    }

    record *getRecordCopy(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getCopy(record);
    }

    bool getRecordIsValid(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->isValid(record);
    }

    string_list *getFieldIds(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getFieldIds(record);
    }

    field_list *getFields(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getFields(record);
    }

    field *getField(jlong message, record *record, const char* fieldId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getField(record, fieldId);
    }

    bool hasField(jlong message, record *record, const char *fieldId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->hasField(record, fieldId);
    }

    string_list *getConditionIds(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getConditionIds(record);
    }

    condition_list *getConditions(jlong message, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getConditions(record);
    }

    condition *getCondition(jlong message, record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->getCondition(record, conditionId);
    }

    bool hasCondition(jlong message, record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRecordUtils()->hasCondition(record, conditionId);
    }

    /*Field Methods*/

    const char *getFieldId(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getId(field);
    }

    const char *getFieldType(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getType(field);
    }

    bool getFieldIsValid(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->isValid(field);
    }

    bool getFieldIsRequired(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->isRequired(field);
    }

    bool getFieldIsNull(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->isNull(field);
    }

    val *getFieldVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getVal(field);
    }

    int getFieldIntVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getIntVal(field);
    }

    long getFieldLongVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getLongVal(field);
    }

    float getFieldFloatVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getFloatVal(field);
    }

    double getFieldDoubleVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getDoubleVal(field);
    }

    signed char getFieldByteVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getByteVal(field);
    }

    const char *getFieldStringVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getStringVal(field);
    }

    bool getFieldBoolVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getBoolVal(field);
    }

    short getFieldShortVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getShortVal(field);
    }

    val_list *getFieldListVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getListVal(field);
    }

    val_map *getFieldMapVal(jlong message, field *field)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->getMapVal(field);
    }

    void setFieldVal(jlong message, field *field, val *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setVal(field, value);
    }

    void setFieldIntVal(jlong message, field *field, int value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setIntVal(field, value);
    }

    void setFieldLongVal(jlong message, field *field, long value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setLongVal(field, value);
    }

    void setFieldFloatVal(jlong message, field *field, float value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setFloatVal(field, value);
    }

    void setFieldDoubleVal(jlong message, field *field, double value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setDoubleVal(field, value);
    }

    void setFieldByteVal(jlong message, field *field, signed char value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setByteVal(field, value);
    }

    void setFieldStringVal(jlong message, field *field, const char *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setStringVal(field, value);
    }

    void setFieldBoolVal(jlong message, field *field, bool value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setBoolVal(field, value);
    }

    void setFieldShortVal(jlong message, field *field, short value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setShortVal(field, value);
    }

    void setFieldListVal(jlong message, field *field, val_list *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setListVal(field, value);
    }

    void setFieldMapVal(jlong message, field *field, val_map *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getFieldUtils()->setMapVal(field, value);
    }

    /*Condition Methods*/

    const char *getConditionId(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getId(condition);
    }

    const char *getConditionType(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getType(condition);
    }

    const char *getConditionOperator(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getOperator(condition);
    }

    bool getConditionIsNull(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->isNull(condition);
    }

    val *getConditionVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getVal(condition);
    }
    
    int getConditionIntVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getIntVal(condition);
    }

    long getConditionLongVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getLongVal(condition);
    }

    float getConditionFloatVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getFloatVal(condition);
    }

    double getConditionDoubleVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getDoubleVal(condition);
    }

    signed char getConditionByteVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getByteVal(condition);
    }

    const char *getConditionStringVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getStringVal(condition);
    }

    bool getConditionBoolVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getBoolVal(condition);
    }

    short getConditionShortVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getShortVal(condition);
    }

    val_list *getConditionListVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getListVal(condition);
    }

    val_map *getConditionMapVal(jlong message, condition *condition)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->getMapVal(condition);
    }

    void setConditionVal(jlong message, condition *condition, val *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setVal(condition, value);
    }

    void setConditionIntVal(jlong message, condition *condition, int value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setIntVal(condition, value);
    }

    void setConditionLongVal(jlong message, condition *condition, long value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setLongVal(condition, value);
    }

    void setConditionFloatVal(jlong message, condition *condition, float value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setFloatVal(condition, value);
    }

    void setConditionDoubleVal(jlong message, condition *condition, double value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setDoubleVal(condition, value);
    }

    void setConditionByteVal(jlong message, condition *condition, signed char value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setByteVal(condition, value);
    }

    void setConditionStringVal(jlong message, condition *condition, const char *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setStringVal(condition, value);
    }

    void setConditionBoolVal(jlong message, condition *condition, bool value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setBoolVal(condition, value);
    }

    void setConditionShortVal(jlong message, condition *condition, short value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setShortVal(condition, value);
    }

    void setConditionListVal(jlong message, condition *condition, val_list *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setListVal(condition, value);
    }

    void setConditionMapVal(jlong message, condition *condition, val_map *value)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getConditionUtils()->setMapVal(condition, value);
    }

    /*List Utility Methods*/

    list_item *getItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getItem(list, index);
    }

    val_list *getListItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getListItem(list, index);
    }

    val_map *getMapItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getMapItem(list, index);
    }

    int getIntItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getIntItem(list, index);
    }

    long getLongItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getLongItem(list, index);
    }

    float getFloatItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getFloatItem(list, index);
    }

    double getDoubleItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getDoubleItem(list, index);
    }

    signed char getByteItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getByteItem(list, index);
    }

    const char *getStringItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getStringItem(list, index);
    }

    bool getBoolItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getBoolItem(list, index);
    }

    short getShortItem(jlong message, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->getShortItem(list, index);
    }

    val_list *createList(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->createList();
    }

    void addItem(jlong message, val_list *list, list_item *item)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addItem(list, item);
    }

    void addIntItem(jlong message, val_list *list, int val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addIntItem(list, val);
    }

    void addLongItem(jlong message, val_list *list, long val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addLongItem(list, val);
    }

    void addFloatItem(jlong message, val_list *list, float val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addFloatItem(list, val);
    }

    void addDoubleItem(jlong message, val_list *list, double val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addDoubleItem(list, val);
    }

    void addByteItem(jlong message, val_list *list, signed char val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addByteItem(list, val);
    }

    void addStringItem(jlong message, val_list *list, const char *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addStringItem(list, val);
    }

    void addBoolItem(jlong message, val_list *list, bool val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addBoolItem(list, val);
    }

    void addShortItem(jlong message, val_list *list, short val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addShortItem(list, val);
    }

    void addListItem(jlong message, val_list *list, val_list *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addListItem(list, val);
    }

    void addMapItem(jlong message, val_list *list, val_map *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getListUtils()->addMapItem(list, val);
    }

    /*Map Utility Methods*/
    val_map *createMap(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->createMap();
    }

    int getSize(jlong message, val_map *map)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getSize(map);
    }

    bool hasKey(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->hasKey(map, key);
    }

    /*Map Value Retrieval Methods*/
    map_val *getVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getVal(map, key);
    }

    jobject getObjectVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getObjectVal(map, key);
    }

    int getIntVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getIntVal(map, key);
    }

    long getLongVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getLongVal(map, key);
    }

    float getFloatVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getFloatVal(map, key);
    }

    double getDoubleVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getDoubleVal(map, key);
    }

    signed char getByteVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getByteVal(map, key);
    }

    const char *getStringVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getStringVal(map, key);
    }

    bool getBoolVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getBoolVal(map, key);
    }

    short getShortVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getShortVal(map, key);
    }

    val_list *getListVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getListVal(map, key);
    }

    val_map *getMapVal(jlong message, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->getMapVal(map, key);
    }

    /*Insert or Update Methods*/
    void putVal(jlong message, val_map *map, const char *key, map_val *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putVal(map, key, val);
    }

    void putObjectVal(jlong message, val_map *map, const char *key, jobject val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putObjectVal(map, key, val);
    }

    void putIntVal(jlong message, val_map *map, const char *key, int val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putIntVal(map, key, val);
    }

    void putLongVal(jlong message, val_map *map, const char *key, long val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putLongVal(map, key, val);
    }

    void putFloatVal(jlong message, val_map *map, const char *key, float val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putFloatVal(map, key, val);
    }

    void putDoubleVal(jlong message, val_map *map, const char *key, double val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putDoubleVal(map, key, val);
    }

    void putByteVal(jlong message, val_map *map, const char *key, signed char val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putByteVal(map, key, val);
    }

    void putStringVal(jlong message, val_map *map, const char *key, const char *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putStringVal(map, key, val);
    }

    void putBoolVal(jlong message, val_map *map, const char *key, bool val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putBoolVal(map, key, val);
    }

    void putShortVal(jlong message, val_map *map, const char *key, short val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putShortVal(map, key, val);
    }

    void putListVal(jlong message, val_map *map, const char *key, val_list *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putListVal(map, key, val);
    }

    void putMapVal(jlong message, val_map *map, const char *key, val_map *val)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getMapUtils()->putMapVal(map, key, val);
    }

    /*Rejection Utils*/
    rejection_list *createRejectionList(jlong message)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->createRejectionList();
    }

    void addRejection(jlong message, rejection_list *rejection_list, rejection *rejection)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->addRejection(rejection_list, rejection);
    }

    rejection *getRejectionCopy(jlong message, rejection *rejection)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->getCopy(rejection);
    }

    record *getRejectionRecord(jlong message, rejection *rejection)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->getRecord(rejection);
    }

    string_list *getRejectionReasons(jlong message, rejection *rejection)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->getReasons(rejection);
    }

    void addRejectionReason(jlong message, rejection *rejection, const char *reason)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getRejectionUtils()->addReason(rejection, reason);
    }

    /*Packet Utils*/
    void addPacketRecord(jlong message, packet *packet, record *record)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->addRecord(packet, record);
    }

    void setPacketRecords(jlong message, packet *packet, record_list *records)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->setRecords(packet, records);
    }

    void addPacketRecords(jlong message, packet *packet, record_list *records)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->addRecords(packet, records);
    }

    void setPacketRejections(jlong message, packet *packet, rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->setRejections(packet, rejections);
    }

    void addPacketRejection(jlong message, packet *packet, rejection *rejection)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->addRejection(packet, rejection);
    }

    void addPacketRejections(jlong message, packet *packet, rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->addRejections(packet, rejections);
    }

    record_list *getPacketRecords(jlong message, packet *packet)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->getRecords(packet);
    }

    rejection_list *getPacketRejections(jlong message, packet *packet)
    {
        return reinterpret_cast<MessageApiEndpoint *>(message)->getPacketUtils()->getRejections(packet);
    }
}