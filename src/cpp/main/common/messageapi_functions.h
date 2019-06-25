#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Field Related Methods
     */


    const char* messageapi_field_getId(struct field *f);
    const char* messageapi_field_getType(struct field *f);
    void* messageapi_field_getValue(struct field *f);

    bool messageapi_field_isRequired(struct field *f);
    bool messageapi_field_isValid(struct field *f);

    bool messageapi_field_setValid(struct field *f, bool isValid);
    void messageapi_field_setType(struct field *f, const char *type);
    void messageapi_field_setValue(struct field *f, void *value);

    /**
     * Condition Related Methods
     */

    const char* messageapi_condition_getId(struct condition *c);
    const char* messageapi_condition_getType(struct condition *c);
    const char* messageapi_condition_getOperator(struct condition *c);

    void* messageapi_condition_getValue(struct condition *c);
    const char* messageapi_condition_setValue(struct condition *c, void *value);

    /**
     * Record Related Methods
     */

    struct field** messageapi_record_getFields(struct record *r);
    struct field* messageapi_record_getField(struct record *r, const char *fieldId);
    bool messageapi_record_hasField(struct record *r, const char *fieldId);

    struct condition** messageapi_record_getConditions(struct record *r);
    struct condition* messageapi_record_getCondition(struct record *r, const char *condId);

    struct record* messageapi_record_getCopy(struct record *r);

    void messageapi_record_setFields(struct record *r, struct field** fields);
    void messageapi_record_setField(struct record *r, void *field, void *value);

    void messageapi_record_setConditions(struct record *r, struct condition **conditions);
    void messageapi_record_setCondition(struct record *r, void *condition, void *value);

    bool messageapi_record_isValid(struct record *r);
    void messageapi_record_setValid(struct record *r, bool valid);

#ifdef __cplusplus
}
#endif
