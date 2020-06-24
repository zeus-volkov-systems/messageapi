#include "RequestUtils.h"

#include <jni.h>

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

/* Default Constructor */
RequestUtils::RequestUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

/* Default Destructor */
RequestUtils::~RequestUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/* Public API */

struct record *RequestUtils::createRecord(struct request *request)
{
    jobject jrecord = this->jvm->CallObjectMethod(request->jrequest, this->createRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

struct request *RequestUtils::getCopy(struct request *request)
{
    jobject jrequest = this->jvm->CallObjectMethod(request->jrequest, this->getCopyDefaultMethodId);
    struct request *requestCopy = (struct request *)malloc(sizeof(struct request) + sizeof(jrequest));
    requestCopy->jrequest = jrequest;
    return requestCopy;
}

struct request *RequestUtils::getCopy(struct request *request, struct val_list *copy_components)
{
    jobject jrequest = this->jvm->CallObjectMethod(request->jrequest, this->getCopyDefaultMethodId, copy_components->jlist);
    struct request *requestCopy = (struct request *)malloc(sizeof(struct request) + sizeof(jrequest));
    requestCopy->jrequest = jrequest;
    return requestCopy;
}

const char *RequestUtils::getType(struct request *request)
{
    jstring jRequestType = static_cast<jstring>(this->jvm->CallObjectMethod(request->jrequest, this->getTypeMethodId));
    const char *requestType = this->typeUtils->fromJavaString(jRequestType);
    this->jvm->DeleteLocalRef(jRequestType);
    return requestType;
}

struct record_list *RequestUtils::getRecords(struct request *request)
{
    jobject jRecords = this->jvm->CallObjectMethod(request->jrequest, this->getRecordsMethodId);
    int recordCount = this->listUtils->getListLength(jRecords);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jRecords;

    return record_list;
}

struct record *RequestUtils::getRequestRecord(struct request *request)
{
    jobject jrecord = this->jvm->CallObjectMethod(request->jrequest, this->getRequestRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

void RequestUtils::setRecords(struct request *request, struct record_list *records)
{
    this->jvm->CallVoidMethod(request->jrequest, this->setRecordsMethodId, records->jrecords);
}

struct response *RequestUtils::submitRequest(struct request *request)
{
    jobject jresponse = this->jvm->CallObjectMethod(request->jrequest, this->submitRequestMethodId);
    struct response *response = (struct response *)malloc(sizeof(struct response) + sizeof(jresponse));
    response->jresponse = jresponse;
    return response;
}

/* Private Methods */

void RequestUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void RequestUtils::loadMethodIds()
{
    jclass requestClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IRequest");

    this->createRecordMethodId = JniUtils::getMethod(this->jvm, requestClass, "createRecord", this->getMethodSignature("createRecord"), false);
    this->getCopyDefaultMethodId = JniUtils::getMethod(this->jvm, requestClass, "getCopy", this->getMethodSignature("getDefaultCopy"), false);
    this->getCopyComponentsMethodId = JniUtils::getMethod(this->jvm, requestClass, "getCopy", this->getMethodSignature("getComponentCopy"), false);
    this->getTypeMethodId = JniUtils::getMethod(this->jvm, requestClass, "getType", this->getMethodSignature("getType"), false);
    this->getRecordsMethodId = JniUtils::getMethod(this->jvm, requestClass, "getRecords", this->getMethodSignature("getRecords"), false);
    this->getRequestRecordMethodId = JniUtils::getMethod(this->jvm, requestClass, "getRequestRecord", this->getMethodSignature("getRequestRecord"), false);
    this->setRecordsMethodId = JniUtils::getMethod(this->jvm, requestClass, "setRecords", this->getMethodSignature("setRecords"), false);
    this->submitRequestMethodId = JniUtils::getMethod(this->jvm, requestClass, "submit", this->getMethodSignature("submitRequest"), false);
    
    jvm->DeleteLocalRef(requestClass);
}


const char *RequestUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "createRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "getDefaultCopy") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRequest;";
    }
    else if (strcmp(methodName, "getComponentCopy") == 0)
    {
        return "(Ljava/util/List;)Lgov/noaa/messageapi/interfaces/IRequest;";
    }
    else if (strcmp(methodName, "getType") == 0)
    {
        return "()Ljava/lang/String;";
    }
    else if (strcmp(methodName, "getRecords") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRequestRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "setRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "submitRequest") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IResponse;";
    }

    return NULL;
}