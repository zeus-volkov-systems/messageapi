#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

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
    struct field_value *getFieldValue(jlong message, struct field *field);

    const char *getConditionId(jlong message, struct condition *condition);
    const char *getConditionType(jlong message, struct condition *condition);
    const char *getConditionOperator(jlong message, struct condition *condition);
    struct condition_value *getConditionValue(jlong message, struct condition *condition);

    int fieldValueAsInteger(jlong message, struct field_value *field_value);
    long fieldValueAsLong(jlong message, struct field_value *field_value);
    float fieldValueAsFloat(jlong message, struct field_value *field_value);
    double fieldValueAsDouble(jlong message, struct field_value *field_value);
    unsigned char fieldValueAsByte(jlong message, struct field_value *field_value);
    const char *fieldValueAsString(jlong message, struct field_value *field_value);
    bool fieldValueAsBoolean(jlong message, struct field_value *field_value);
    short fieldValueAsShort(jlong message, struct field_value *field_value);

    int conditionValueAsInteger(jlong message, struct condition_value *condition_value);
    long conditionValueAsLong(jlong message, struct condition_value *condition_value);
    float conditionValueAsFloat(jlong message, struct condition_value *condition_value);
    double conditionValueAsDouble(jlong message, struct condition_value *condition_value);
    unsigned char conditionValueAsByte(jlong message, struct condition_value *condition_value);
    const char *conditionValueAsString(jlong message, struct condition_value *condition_value);
    bool conditionValueAsBoolean(jlong message, struct condition_value *condition_value);
    short conditionValueAsShort(jlong message, struct condition_value *condition_value);

#ifdef __cplusplus
}
#endif
