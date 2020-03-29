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

    struct string_list *getFieldNames(jlong message, struct record *record);
    struct field_list *getFields(jlong message, struct record *record);

#ifdef __cplusplus
}
#endif
