#include "RejectionUtils.h"

#include <jni.h>


/*Constructor*/

RejectionUtils::RejectionUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

/*Destructor*/

RejectionUtils::~RejectionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/*Public API*/

struct rejection_list *RejectionUtils::createRejectionList()
{
    jobject jList = this->jvm->NewObject(this->typeUtils->getListClass(), this->listUtils->createListMethod());
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = 0;
    rejection_list->jrejections = jList;
    return rejection_list;
}

void RejectionUtils::addRejection(struct rejection_list *rejection_list, struct rejection *rejection)
{
    this->jvm->CallVoidMethod(rejection_list->jrejections, this->listUtils->addListItemMethod(), rejection->jrejection);
    rejection_list->count += 1;
}

struct rejection *RejectionUtils::getCopy(struct rejection *rejection)
{
    jobject jRejectionCopy = this->jvm->CallObjectMethod(rejection->jrejection, this->getCopyMethodId);
    struct rejection *rejectionCopy = (struct rejection *)malloc(sizeof(struct rejection) + sizeof(jRejectionCopy));
    rejectionCopy->jrejection = jRejectionCopy;
    return rejectionCopy;
}

struct record *RejectionUtils::getRecord(struct rejection *rejection)
{
    jobject jRecord = this->jvm->CallObjectMethod(rejection->jrejection, this->getRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jRecord));
    record->jrecord = jRecord;
    return record;
}

struct string_list *RejectionUtils::getReasons(struct rejection *rejection)
{
    jobject jReasons = this->jvm->CallObjectMethod(rejection->jrejection, this->getReasonsMethodId);
    struct string_list *reasons = this->listUtils->translateStringList(jReasons);
    return reasons;
}

void RejectionUtils::addReason(struct rejection *rejection, const char *reason)
{
    jstring jReason = this->typeUtils->toJavaString(reason);
    this->jvm->CallVoidMethod(rejection->jrejection, this->addReasonMethodId, jReason);
}

/*Private Methods*/
void RejectionUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void RejectionUtils::loadMethodIds()
{
    jclass rejectionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IRejection");
    this->getCopyMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getCopy", this->getMethodSignature("getCopy"), false);
    this->getReasonsMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getReasons", this->getMethodSignature("getReasons"), false);
    this->getRecordMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "getRecord", this->getMethodSignature("getRecord"), false);
    this->addReasonMethodId = JniUtils::getMethod(this->jvm, rejectionClass, "addReason", this->getMethodSignature("addReason"), false);
    this->jvm->DeleteLocalRef(rejectionClass);
}

const char *RejectionUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getCopy") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRejection;";
    }
    else if (strcmp(methodName, "getReasons") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "addReason") == 0)
    {
        return "(Ljava/lang/String;)V";
    }

    return NULL;
}