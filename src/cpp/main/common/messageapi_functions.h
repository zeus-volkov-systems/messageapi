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


    char* messageapi_field_getId(field*);
    char* messageapi_field_getType(field*);
    void* messageapi_field_getValue(field*);

    bool messageapi_field_isRequired(field*);
    bool messageapi_field_isValid(field*);

    bool messageapi_field_setValid(field*, bool);
    void messageapi_field_setType(field*, const char*);
    void messageapi_field_setValue(struct field *, void *);

#ifdef __cplusplus
}
#endif
