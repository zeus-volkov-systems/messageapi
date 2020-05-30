#include "ResponseUtils.h"

#include <jni.h>

/**
 * Responses are returned by calling submit on a request. Responses operate asynchronously,
 * setting an isComplete flag from false to true whenever the specified process is complete.
 * Responses execute the request, and holds any records and/or rejections
 * that are returned by the evaluation of the request. These records are an aggregate of all
 * computation paths through a given request, so may contain records gathered from multiple sources
 * in the same computation.
 * 
 * @author Ryan Berkheimer
 */

/* Default Constructor */
ResponseUtils::ResponseUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

/* Default Destructor */
ResponseUtils::~ResponseUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/* Public API */

bool ResponseUtils::isComplete(struct response *response)
{
    return (bool)this->jvm->CallBooleanMethod(response->jresponse, this->isCompleteMethodId);
}

struct request *ResponseUtils::getRequest(struct response *response)
{
    jobject jrequest = this->jvm->CallObjectMethod(response->jresponse, this->getRequestMethodId);
    struct request *request = (struct request *)malloc(sizeof(struct request) + sizeof(jrequest));
    request->jrequest = jrequest;
    return request;
}

struct rejection_list *ResponseUtils::getRejections(struct response *response)
{
    jobject jRejections = this->jvm->CallObjectMethod(response->jresponse, this->getRejectionsMethodId);
    int rejectionCount = this->listUtils->getListLength(jRejections);
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = rejectionCount;
    rejection_list->jrejections = jRejections;

    return rejection_list;
}

struct record_list *ResponseUtils::getRecords(struct response *response)
{
    jobject jRecords = this->jvm->CallObjectMethod(response->jresponse, this->getRecordsMethodId);
    int recordCount = this->listUtils->getListLength(jRecords);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jRecords;

    return record_list;
}

void ResponseUtils::setRejections(struct response *response, struct rejection_list *rejections)
{
    this->jvm->CallVoidMethod(response->jresponse, this->setRejectionsMethodId, rejections->jrejections);
}

void ResponseUtils::setRecords(struct response *response, struct record_list *records)
{
    this->jvm->CallVoidMethod(response->jresponse, this->setRecordsMethodId, records->jrecords);
}

void ResponseUtils::setComplete(struct response *response, bool isComplete)
{
    jobject jBoolVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)isComplete);
    this->jvm->CallVoidMethod(response->jresponse, this->setCompleteMethodId, jBoolVal);
    this->jvm->DeleteLocalRef(jBoolVal);
}

/* Private Methods */

void ResponseUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void ResponseUtils::loadMethodIds()
{
    jclass responseClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IResponse");

    this->isCompleteMethodId = JniUtils::getMethod(this->jvm, responseClass, "isComplete", this->getMethodSignature("isComplete"), false);
    this->getRequestMethodId = JniUtils::getMethod(this->jvm, responseClass, "getRequest", this->getMethodSignature("getRequest"), false);
    this->getRejectionsMethodId = JniUtils::getMethod(this->jvm, responseClass, "getRejections", this->getMethodSignature("getRejections"), false);
    this->getRecordsMethodId = JniUtils::getMethod(this->jvm, responseClass, "getRecords", this->getMethodSignature("getRecords"), false);
    this->setRejectionsMethodId = JniUtils::getMethod(this->jvm, responseClass, "setRejections", this->getMethodSignature("setRejections"), false);
    this->setRecordsMethodId = JniUtils::getMethod(this->jvm, responseClass, "setRecords", this->getMethodSignature("setRecords"), false);
    this->setCompleteMethodId = JniUtils::getMethod(this->jvm, responseClass, "setComplete", this->getMethodSignature("setComplete"), false);

    jvm->DeleteLocalRef(responseClass);
}


const char *ResponseUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "isComplete") == 0)
    {
        return "()Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getRequest") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRequest;";
    }
    else if (strcmp(methodName, "getRejections") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecords") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "setRejections") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "setRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "setComplete") == 0)
    {
        return "(Ljava/lang/Boolean;)V";
    }
    return NULL;
}