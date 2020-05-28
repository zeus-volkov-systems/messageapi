
#ifndef _REQUESTUTILS_H
#define _REQUESTUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>
#include "ListUtils.h"
#include "TypeUtils.h"

/**
 * A Request holds a request record (with request-global filtering conditions), and a record set.
 * To set values for conditions in the request record, grab the request record, then grab the
 * conditions list (or simply set the named condition directly).
 * 
 * A request workflow is generally...
 * create a record; set field (and possibly condition) values on that record; repeat for
 * as many records in the set;
 * optionally set request-wide filtering conditions on the request record;
 * submit the request and get the async response.
 * 
 * Use note:
 * Remember that all factoring and filtering happens after the request is submitted.
 * This should serve as a hint that if you are going to do some joins on linked multi-dimensional data,
 * you should pass both datasets into the request as records. You don't have to set a value for every field.
 * 
 * Once you submit, look at your manifest to see how the request is split into multiple parts. Request record
 * conditions can be assigned to any container. So for example, you can set a request-record condition of
 * 
 * 'has_position_field=true', and then assign the 'has_position_field' condition to a container in your manifest,
 * so that the container in question will only get records in which the field in question satisfies the condition.
 *  
 * @author Ryan Berkheimer
 */
class RequestUtils
{

public:
    /*Default constructor/destructors*/
    RequestUtils(JNIEnv *javaEnv, TypeUtils *typeUtils, ListUtils *listUtils);
    ~RequestUtils();

    /*Request Methods*/
    struct record *createRecord(struct request *request);
    struct request *getCopy(struct request *request);
    struct request *getCopy(struct request *request, struct val_list *copy_components);
    const char *getType(struct request *request);
    struct record_list *getRecords(struct request *request);
    struct record *getRequestRecord(struct request *request);
    void setRecords(struct request *request, struct record_list *records);
    struct response *submitRequest(struct request *request);

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;
    TypeUtils *typeUtils;

    /*Request Methods*/
    jmethodID createRecordMethodId;
    jmethodID getCopyDefaultMethodId;
    jmethodID getCopyComponentsMethodId;
    jmethodID getTypeMethodId;
    jmethodID getRecordsMethodId;
    jmethodID getRequestRecordMethodId;
    jmethodID setRecordsMethodId;
    jmethodID submitRequestMethodId;


    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils, ListUtils *listUtils);

    /*Grouped methods for returning the matching method signature string for a given interface*/
    const char *getMethodSignature(const char *methodName);
};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
