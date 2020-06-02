#include "MessageApiSession.h"

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
MessageApiSession::MessageApiSession(JNIEnv *env, jobject session)
{
    this->jvm = env;
    this->session = this->jvm->NewGlobalRef(session);

    this->typeUtils = new TypeUtils(this->jvm);
    this->listUtils = new ListUtils(this->jvm, typeUtils);
    this->mapUtils = new MapUtils(this->jvm, typeUtils);
    this->sessionUtils = new SessionUtils(this->jvm, this->session);
    this->requestUtils = new RequestUtils(this->jvm, this->typeUtils, this->listUtils);
    this->responseUtils = new ResponseUtils(this->jvm, this->typeUtils, this->listUtils);
    this->recordUtils = new RecordUtils(this->jvm, this->typeUtils, this->listUtils);
    this->rejectionUtils = new RejectionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->fieldUtils = new FieldUtils(this->jvm, this->typeUtils, this->listUtils, this->mapUtils);
    this->conditionUtils = new ConditionUtils(this->jvm, this->typeUtils, this->listUtils, this->mapUtils);
    this->packetUtils = new PacketUtils(this->jvm, this->listUtils);
}

MessageApiSession::~MessageApiSession()
{
    try
    {
        delete this->sessionUtils;
        delete this->requestUtils;
        delete this->responseUtils;
        delete this->recordUtils;
        delete this->rejectionUtils;
        delete this->fieldUtils;
        delete this->conditionUtils;
        delete this->packetUtils;
        delete this->listUtils;
        delete this->mapUtils;
        delete this->typeUtils;
        this->jvm->DeleteGlobalRef(this->session);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

SessionUtils *MessageApiSession::getSessionUtils()
{
    return this->sessionUtils;
}

RequestUtils *MessageApiSession::getRequestUtils()
{
    return this->requestUtils;
}

ResponseUtils *MessageApiSession::getResponseUtils()
{
    return this->responseUtils;
}

RecordUtils *MessageApiSession::getRecordUtils()
{
    return this->recordUtils;
}

RejectionUtils *MessageApiSession::getRejectionUtils()
{
    return this->rejectionUtils;
}

FieldUtils *MessageApiSession::getFieldUtils()
{
    return this->fieldUtils;
}

ConditionUtils *MessageApiSession::getConditionUtils()
{
    return this->conditionUtils;
}

PacketUtils *MessageApiSession::getPacketUtils()
{
    return this->packetUtils;
}

ListUtils *MessageApiSession::getListUtils()
{
    return this->listUtils;
}

MapUtils *MessageApiSession::getMapUtils()
{
    return this->mapUtils;
}

TypeUtils *MessageApiSession::getTypeUtils()
{
    return this->typeUtils;
}



