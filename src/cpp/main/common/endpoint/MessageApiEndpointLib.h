#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    /*Endpoint Methods*/
    struct record *getStateContainer(jlong message);
    struct field_list *getDefaultFields(jlong message);
    struct packet *createPacket(jlong message);
    struct record *createRecord(jlong message);
    struct rejection *createRejection(jlong message, struct record *record, const char *reason);

    /*Protocol Record Methods*/
    struct record_list *getRecords(jlong message);
    struct record_list *getRecordsByCollection(jlong message, const char *collection);
    struct record_list *getRecordsByTransformation(jlong message, const char *transformation);
    struct record_list *getRecordsByUUID(jlong message, const char *uuid);
    struct record_list *getRecordsByClassifier(jlong message, const char *key, const char *value);
    struct record *getRecord(jlong message, struct record_list *recordList, int recordIndex);

    /*Record Methods*/
    struct record_list *createRecordList(jlong message);
    void addRecordEntry(jlong message, struct record_list *record_list, struct record *record);

    struct record *getRecordCopy(jlong message, struct record *record);
    bool getRecordIsValid(jlong message, struct record *record);

    struct string_list *getFieldIds(jlong message, struct record *record);
    struct field_list * getFields(jlong message, struct record *record);
    struct field * getField(jlong message, struct record *record, const char *fieldId);
    bool hasField(jlong message, struct record *record, const char *fieldId);

    struct string_list *getConditionIds(jlong message, struct record *record);
    struct condition_list *getConditions(jlong message, struct record *record);
    struct condition *getCondition(jlong message, struct record *record, const char *conditionId);
    bool hasCondition(jlong message, struct record *record, const char *conditionId);

    /*Rejection Methods*/
    struct rejection_list *createRejectionList(jlong message);
    void addRejectionEntry(jlong message, struct rejection_list *rejection_list, struct rejection *rejection);
    struct rejection *getRejectionCopy(jlong message, struct rejection *rejection);
    struct record *getRejectionRecord(jlong message, struct rejection *rejection);
    struct string_list *getRejectionReasons(jlong message, struct rejection *rejection);
    void addRejectionReason(jlong message, struct rejection *rejection, const char *reason);

    /*Field Methods*/
    const char *getFieldId(jlong message, struct field *field);
    const char * getFieldType(jlong message, struct field *field);
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

    /*List Utility Methods*/
    int getIntEntry(jlong message, struct val_list *list, int index);
    long getLongEntry(jlong message, struct val_list *list, int index);
    float getFloatEntry(jlong message, struct val_list *list, int index);
    double getDoubleEntry(jlong message, struct val_list *list, int index);
    signed char getByteEntry(jlong message, struct val_list *list, int index);
    const char *getStringEntry(jlong message, struct val_list *list, int index);
    bool getBoolEntry(jlong message, struct val_list *list, int index);
    short getShortEntry(jlong message, struct val_list *list, int index);
    struct list_entry *getEntry(jlong message, struct val_list *list, int index);
    struct val_list *getListEntry(jlong message, struct val_list *list, int index);
    struct val_list *createList(jlong message);
    void addEntry(jlong message, struct val_list *list, struct list_entry *entry);
    void addIntEntry(jlong message, struct val_list *list, int val);
    void addLongEntry(jlong message, struct val_list *list, long val);
    void addFloatEntry(jlong message, struct val_list *list, float val);
    void addDoubleEntry(jlong message, struct val_list *list, double val);
    void addByteEntry(jlong message, struct val_list *list, signed char val);
    void addStringEntry(jlong message, struct val_list *list, const char *val);
    void addBoolEntry(jlong message, struct val_list *list, bool val);
    void addShortEntry(jlong message, struct val_list *list, short val);
    void addListEntry(jlong message, struct val_list *list, struct val_list *val);

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
