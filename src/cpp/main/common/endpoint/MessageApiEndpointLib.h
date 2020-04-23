#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    struct record *getStateContainer(jlong message);
    struct field_list *getDefaultFields(jlong message);
    struct packet *createPacket(jlong message);
    struct record *createRecord(jlong message);
    struct rejection *createRejection(jlong message, struct record *record, const char *reason);

    struct record_list *getRecords(jlong message);
    struct record_list *getRecordsByCollection(jlong message, const char *collection);
    struct record_list *getRecordsByTransformation(jlong message, const char *transformation);
    struct record_list *getRecordsByUUID(jlong message, const char *uuid);
    struct record_list *getRecordsByClassifier(jlong message, const char *key, const char *value);
    struct record *getRecord(jlong message, struct record_list *recordList, int recordIndex);

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

    const char *getFieldId(jlong message, struct field *field);
    const char * getFieldType(jlong message, struct field *field);
    bool getFieldIsValid(jlong message, struct field *field);
    bool getFieldIsRequired(jlong message, struct field *field);
    struct value *getFieldVal(jlong message, struct field *field);

    const char *getConditionId(jlong message, struct condition *condition);
    const char *getConditionType(jlong message, struct condition *condition);
    const char *getConditionOperator(jlong message, struct condition *condition);
    struct condition_value *getConditionValue(jlong message, struct condition *condition);

    int valAsInt(jlong message, struct value *value);
    long valAsLong(jlong message, struct value *value);
    float valAsFloat(jlong message, struct value *value);
    double valAsDouble(jlong message, struct value *value);
    unsigned char valAsByte(jlong message, struct value *value);
    const char *valAsString(jlong message, struct value *value);
    bool valAsBool(jlong message, struct value *value);
    short valAsShort(jlong message, struct value *value);
    struct val_list *valAsList(jlong message, struct value *value);

    int getIntEntry(jlong message, struct val_list *list, int index);
    long getLongEntry(jlong message, struct val_list *list, int index);
    float getFloatEntry(jlong message, struct val_list *list, int index);
    double getDoubleEntry(jlong message, struct val_list *list, int index);
    unsigned char getByteEntry(jlong message, struct val_list *list, int index);
    const char *getStringEntry(jlong message, struct val_list *list, int index);
    bool getBoolEntry(jlong message, struct val_list *list, int index);
    short getShortEntry(jlong message, struct val_list *list, int index);
    jobject getListEntry(jlong message, struct val_list *list, int index);

#ifdef __cplusplus
}
#endif
