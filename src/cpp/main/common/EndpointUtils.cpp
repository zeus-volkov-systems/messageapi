#include "EndpointUtils.h"

#include <jni.h>


/**
Constructor for the Endpoint object.
*/
EndpointUtils::EndpointUtils(JNIEnv *jvm, jobject endpoint, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, endpoint, typeUtils, listUtils);
    this->loadMethodIds();
}

EndpointUtils::~EndpointUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/*Public API*/
struct record *EndpointUtils::getStateContainer()
{
    jobject jstatecontainer = this->jvm->CallObjectMethod(this->endpoint, this->getStateContainerMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jstatecontainer));
    record->jrecord = jstatecontainer;
    return record;
}

struct field_list *EndpointUtils::getDefaultFields()
{
    jobject jFieldList = this->jvm->CallObjectMethod(this->endpoint, this->getDefaultFieldsMethodId);

    int fieldCount = this->listUtils->getListLength(jFieldList);
    struct field **fields = (struct field **)malloc(sizeof(struct field *) * fieldCount);

    for (int i = 0; i < fieldCount; i++)
    {
        jobject jfield = static_cast<jobject>(this->jvm->CallObjectMethod(jFieldList, this->listUtils->getListItemMethod(), i));
        struct field *field = (struct field *)malloc(sizeof(field) + sizeof(jfield));
        field->jfield = (jobject)jfield;
        fields[i] = field;
    }

    struct field_list *field_list = (struct field_list *)malloc(sizeof(struct field_list) + sizeof(fields));
    field_list->count = fieldCount;
    field_list->fields = fields;
    return field_list;
}

struct val_map *EndpointUtils::getConstructor()
{
    jobject jMap = this->jvm->CallObjectMethod(this->endpoint, this->getConstructorMethodId);
    struct val_map *map = (struct val_map *)malloc(sizeof(struct val_map));
    map->jmap = jMap;
    return map;
}

struct packet *EndpointUtils::createPacket()
{
    jobject jpacket = this->jvm->CallObjectMethod(this->endpoint, this->createPacketMethodId);
    struct packet *packet = (struct packet *)malloc(sizeof(struct packet) + sizeof(jpacket));
    packet->jpacket = jpacket;
    return packet;
}

struct record *EndpointUtils::createRecord()
{
    jobject jrecord = this->jvm->CallObjectMethod(this->endpoint, this->createRecordMethodId);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

struct rejection *EndpointUtils::createRejection(struct record *record, const char *reason)
{
    jstring jreason = this->typeUtils->toJavaString(reason);
    jobject jrejection = this->jvm->CallObjectMethod(this->endpoint, this->createRejectionMethodId, record->jrecord, jreason);
    struct rejection *rejection = (struct rejection *)malloc(sizeof(struct rejection) + sizeof(jrejection));
    rejection->jrejection = jrejection;
    this->jvm->DeleteLocalRef(jreason);
    return rejection;
}

/*Private Methods*/

void EndpointUtils::loadGlobalRefs(JNIEnv *jvm, jobject endpoint, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->endpoint = endpoint;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void EndpointUtils::loadMethodIds()
{
    jclass endpointClass = JniUtils::getObjectClass(this->jvm, this->endpoint);
    this->getStateContainerMethodId = JniUtils::getMethod(this->jvm, endpointClass, "getStateContainer", this->getMethodSignature("getStateContainer"), false);
    this->getDefaultFieldsMethodId = JniUtils::getMethod(this->jvm, endpointClass, "getDefaultFields", this->getMethodSignature("getDefaultFields"), false);
    this->getConstructorMethodId = JniUtils::getMethod(this->jvm, endpointClass, "getConstructor", this->getMethodSignature("getConstructor"), false);
    this->createPacketMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createPacket", this->getMethodSignature("createPacket"), false);
    this->createRecordMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createRecord", this->getMethodSignature("createRecord"), false);
    this->createRejectionMethodId = JniUtils::getMethod(this->jvm, endpointClass, "createRejection", this->getMethodSignature("createRejection"), false);
    this->jvm->DeleteLocalRef(endpointClass);
}

const char *EndpointUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "getStateContainer") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "getDefaultFields") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getConstructor") == 0)
    {
        return "()Ljava/util/Map;";
    }
    else if (strcmp(methodName, "createPacket") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IPacket;";
    }
    else if (strcmp(methodName, "createRecord") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "createRejection") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRecord;Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/IRejection;";
    }
    return NULL;
}