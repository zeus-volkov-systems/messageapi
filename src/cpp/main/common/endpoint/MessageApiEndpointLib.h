#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    struct record_list * getRecords(jlong message);
    struct record_list * getRecordsByCollection(jlong message, const char *collection);
    struct record_list * getRecordsByTransformation(jlong message, const char *transformation);
    struct record_list * getRecordsByUUID(jlong message, const char *uuid);
    struct record_list * getRecordsByClassifier(jlong message, const char *key, const char *value);
    struct record * getRecord(jlong message, struct record_list * recordList, int recordIndex);

    struct string_list * getFieldIds(jlong message, struct record *record);
    struct field_list * getFields(jlong message, struct record *record);
    struct field * getField(jlong message, struct record *record, const char *fieldId);
    const char * getFieldId(jlong message, struct field *field);
    const char * getFieldType(jlong message, struct field *field);
    struct field_value * getFieldValue(jlong message, struct field *field);
    int fieldValueAsInteger(jlong message, struct field_value *field_value);
    bool getFieldIsValid(jlong message, struct field *field);
    bool getFieldIsRequired(jlong message, struct field *field);

#ifdef __cplusplus
}
#endif
