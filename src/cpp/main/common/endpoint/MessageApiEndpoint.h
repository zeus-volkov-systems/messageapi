
#ifndef _Included_MessageApiEndpoint
#define _Included_MessageApiEndpoint

#include <jni.h>
#include <stdbool.h>
#include "endpoint_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

/**
 * This is the header for the MessageApiEndpoint class - this class is the native side facility
 * for doing endpoint processing and communicating back with the java side. This class holds
 * three private vars - a pointer to the jvm where the call originated from, a pointer to the
 * endpoint class instance (jobject), and a pointer to the protocol record that holds data for
 * this endpoint to process (jobject). To the user of the MessageApiEndpoint library in the native side,
 * they will see the entire library as a single jlong. This jlong holds a pointer to this class,
 * making it easier for implementors to ignore most of the details of implementation.
 * @author Ryan Berkheimer
 */
class MessageApiEndpoint
{

public:
    MessageApiEndpoint(JNIEnv* javaEnv, jobject jEndpoint, jobject jProtocolRecord);
    ~MessageApiEndpoint();

    jobject getProtocolRecords(const char *method, const char *key, const char *val);

    struct record_list * getRecords(const char *method, const char *key = NULL, const char *val = NULL);
    struct record * getRecord(struct record_list *record_list, int index);
    struct string_list *getFieldIds(struct record *record);
    struct field_list * getFields(struct record *record);
    struct field * getField(struct record *record, const char* fieldId);
    const char * getFieldId(struct field *field);
    const char * getFieldType(struct field *field);
    struct field_value * getFieldValue(struct field *field);
    int fieldValueAsInteger(struct field_value *field_value);
    bool getFieldIsValid(struct field *field);
    bool getFieldIsRequired(struct field *field);

private:
    JNIEnv* jvm;
    jobject endpoint;
    jobject protocolRecord;
    jclass jException;

    jmethodID getJBoolMethodId;
    jmethodID makeJBoolMethodId;
    jmethodID getJByteMethodId;
    jmethodID makeJByteMethodId;
    jmethodID getJIntMethodId;
    jmethodID makeJIntMethodId;
    jmethodID getJLongMethodId;
    jmethodID makeJLongMethodId;
    jmethodID getJFloatMethodId;
    jmethodID makeJFloatMethodId;
    jmethodID getJDoubleMethodId;
    jmethodID makeJDoubleMethodId;
    jmethodID getJStringMethodId;
    jmethodID makeJStringMethodId;
    jmethodID getJListSizeMethodId;
    jmethodID getJListItemMethodId;

    jmethodID getRecordsMethodId;
    jmethodID getRecordsByCollectionMethodId;
    jmethodID getRecordsByUUIDMethodId;
    jmethodID getRecordsByTransformationMethodId;
    jmethodID getRecordsByClassifierMethodId;

    void loadTypeMethodIds();
    void loadRecordRefs();
    void releaseProtocolRecordRefs();
    void loadGlobalTypeRefs();

    void checkAndThrow(const char *errorMessage);

    jclass getNamedClass(const char *javaClassName);
    jclass getObjectClass(jobject javaObject);
    jmethodID getMethod(jclass javaClass, const char *methodName, const char *methodSignature, bool isStatic);
    jstring toJavaString(const char *charString);
    const char *fromJavaString(jstring javaString);
    const char *getRecordMethodSignature(const char *recordMethodName);
    const char *getFieldMethodSignature(const char *fieldMethodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
