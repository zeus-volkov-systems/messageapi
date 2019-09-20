#include <stdbool.h>

/**
 * @author Ryan Berkheimer
 */
#ifdef __cplusplus
extern "C"
{
#endif

    struct records_vector* getRecords(jlong);
    struct records_vector* getRecordsByCollection(jlong, const char*);
    struct records_vector* getRecordsByTransformation(jlong, const char*);
    struct records_vector* getRecordsByUUID(jlong, const char*);
    struct records_vector* getRecordsByClassifier(jlong, const char*, const char*);

#ifdef __cplusplus
}
#endif
