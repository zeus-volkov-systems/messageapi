#include "MessageApiEndpoint.h"

#include <iostream>
#include <string>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Constructor for the MessageApiEndpoint object. Takes a JNI environment pointer, an endpoint context (this refers to
the endpoint class that's instantiating the object), and a protocol record which holds containers of records.
*/
MessageApiEndpoint::MessageApiEndpoint(JNIEnv *env, jobject jendpoint, jobject jprotocolRecord)
{
    this->jvm = env;
    this->endpoint = this->jvm->NewGlobalRef(jendpoint);
    this->protocolRecord = this->jvm->NewGlobalRef(jprotocolRecord);

    this->typeUtils = new TypeUtils(this->jvm);
    this->listUtils = new ListUtils(this->jvm, typeUtils);
    this->mapUtils = new MapUtils(this->jvm, typeUtils);
    this->endpointUtils = new EndpointUtils(this->jvm, this->endpoint, this->typeUtils, this->listUtils);
    this->protocolRecordUtils = new ProtocolRecordUtils(this->jvm, this->protocolRecord, this->typeUtils, this->listUtils);
    this->recordUtils = new RecordUtils(this->jvm, this->typeUtils, this->listUtils);
    this->rejectionUtils = new RejectionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->fieldUtils = new FieldUtils(this->jvm, this->typeUtils, this->listUtils);
    this->conditionUtils = new ConditionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->packetUtils = new PacketUtils(this->jvm, this->listUtils);

}

MessageApiEndpoint::~MessageApiEndpoint()
{
    try
    {
        delete this->endpointUtils;
        delete this->protocolRecordUtils;
        delete this->recordUtils;
        delete this->rejectionUtils;
        delete this->fieldUtils;
        delete this->conditionUtils;
        delete this->packetUtils;
        delete this->listUtils;
        delete this->mapUtils;
        delete this->typeUtils;
        this->jvm->DeleteGlobalRef(this->endpoint);
        this->jvm->DeleteGlobalRef(this->protocolRecord);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

EndpointUtils *MessageApiEndpoint::getEndpointUtils()
{
    return this->endpointUtils;
}

ProtocolRecordUtils *MessageApiEndpoint::getProtocolRecordUtils()
{
    return this->protocolRecordUtils;
}

RecordUtils *MessageApiEndpoint::getRecordUtils()
{
    return this->recordUtils;
}

RejectionUtils *MessageApiEndpoint::getRejectionUtils()
{
    return this->rejectionUtils;
}

FieldUtils *MessageApiEndpoint::getFieldUtils()
{
    return this->fieldUtils;
}

ConditionUtils *MessageApiEndpoint::getConditionUtils()
{
    return this->conditionUtils;
}

PacketUtils *MessageApiEndpoint::getPacketUtils()
{
    return this->packetUtils;
}

ListUtils *MessageApiEndpoint::getListUtils()
{
    return this->listUtils;
}

MapUtils *MessageApiEndpoint::getMapUtils()
{
    return this->mapUtils;
}

TypeUtils *MessageApiEndpoint::getTypeUtils()
{
    return this->typeUtils;
}



