#include "PacketUtils.h"
#include "JniUtils.h"

#include <jni.h>


/**
Constructor for the MessageApiEndpoint object. Takes a JNI environment pointer, an endpoint context (this refers to
the endpoint class that's instantiating the object), and a protocol record which holds containers of records.
*/
PacketUtils::PacketUtils(JNIEnv *jvm, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, listUtils);
    this->loadMethodIds();
}

PacketUtils::~PacketUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void PacketUtils::loadGlobalRefs(JNIEnv *jvm, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->listUtils = listUtils;
}

void PacketUtils::loadMethodIds()
{
    jclass packetClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IPacket");
    this->setRecordsMethodId = JniUtils::getMethod(this->jvm, packetClass, "setRecords", this->getMethodSignature("setRecords"), false);
    this->addRecordMethodId = JniUtils::getMethod(this->jvm, packetClass, "addRecord", this->getMethodSignature("addRecord"), false);
    this->addRecordsMethodId = JniUtils::getMethod(this->jvm, packetClass, "addRecords", this->getMethodSignature("addRecords"), false);
    this->setRejectionsMethodId = JniUtils::getMethod(this->jvm, packetClass, "setRejections", this->getMethodSignature("setRejections"), false);
    this->addRejectionMethodId = JniUtils::getMethod(this->jvm, packetClass, "addRejection", this->getMethodSignature("addRejection"), false);
    this->addRejectionsMethodId = JniUtils::getMethod(this->jvm, packetClass, "addRejections", this->getMethodSignature("addRejections"), false);
    this->getRecordsMethodId = JniUtils::getMethod(this->jvm, packetClass, "getRecords", this->getMethodSignature("getRecords"), false);
    this->getRejectionsMethodId = JniUtils::getMethod(this->jvm, packetClass, "getRejections", this->getMethodSignature("getRejections"), false);
    jvm->DeleteLocalRef(packetClass);
}


const char *PacketUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "setRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "addRecord") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRecord;)V";
    }
    else if (strcmp(methodName, "addRecords") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "setRejections") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "addRejection") == 0)
    {
        return "(Lgov/noaa/messageapi/interfaces/IRejection;)V";
    }
    else if (strcmp(methodName, "addRejections") == 0)
    {
        return "(Ljava/util/List;)V";
    }
    else if (strcmp(methodName, "getRecords") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getRejections") == 0)
    {
        return "()Ljava/util/List;";
    }
    return NULL;
}

void PacketUtils::setRecords(struct packet *packet, struct record_list *records)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->setRecordsMethodId, records->jrecords);
}

void PacketUtils::addRecord(struct packet *packet, struct record *record)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addRecordMethodId, record->jrecord);
}

void PacketUtils::addRecords(struct packet *packet, struct record_list *records)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addRecordsMethodId, records->jrecords);
}

void PacketUtils::setRejections(struct packet *packet, struct rejection_list *rejections)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->setRejectionsMethodId, rejections->jrejections);
}

void PacketUtils::addRejection(struct packet *packet, struct rejection *rejection)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addRejectionMethodId, rejection->jrejection);
}

void PacketUtils::addRejections(struct packet *packet, struct rejection_list *rejections)
{
    this->jvm->CallVoidMethod(packet->jpacket, this->addRejectionsMethodId, rejections->jrejections);
}

struct record_list *PacketUtils::getRecords(struct packet *packet)
{
    jobject jPacketRecords = this->jvm->CallObjectMethod(packet->jpacket, this->getRecordsMethodId);
    int recordCount = this->listUtils->getListLength(jPacketRecords);
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = recordCount;
    record_list->jrecords = jPacketRecords;

    return record_list;
}

struct rejection_list *PacketUtils::getRejections(struct packet *packet)
{
    jobject jPacketRejections = this->jvm->CallObjectMethod(packet->jpacket, this->getRejectionsMethodId);
    int rejectionCount = this->listUtils->getListLength(jPacketRejections);
    struct rejection_list *rejection_list = (struct rejection_list *)malloc(sizeof(struct rejection_list));
    rejection_list->count = rejectionCount;
    rejection_list->jrejections = jPacketRejections;

    return rejection_list;
}
