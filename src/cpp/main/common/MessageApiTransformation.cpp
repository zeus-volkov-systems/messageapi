#include "MessageApiTransformation.h"

#include <iostream>
#include <string>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Constructor for the MessageApiTransformation object. Takes a JNI environment pointer, a transformation context (this refers to
the transformation class that's instantiating the object), and a transformation record which holds containers of records.
*/
MessageApiTransformation::MessageApiTransformation(JNIEnv *env, jobject jtransformation, jobject jTransformationMap)
{
    this->jvm = env;
    this->transformation = this->jvm->NewGlobalRef(jtransformation);
    this->transformationMap = this->jvm->NewGlobalRef(jTransformationMap);

    this->typeUtils = new TypeUtils(this->jvm);
    this->listUtils = new ListUtils(this->jvm, typeUtils);
    this->mapUtils = new MapUtils(this->jvm, typeUtils);
    this->transformationUtils = new TransformationUtils(this->jvm, this->transformation, this->transformationMap, this->typeUtils, this->mapUtils, this->listUtils);
    this->recordUtils = new RecordUtils(this->jvm, this->typeUtils, this->listUtils);
    this->rejectionUtils = new RejectionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->fieldUtils = new FieldUtils(this->jvm, this->typeUtils, this->listUtils);
    this->conditionUtils = new ConditionUtils(this->jvm, this->typeUtils, this->listUtils);
    this->packetUtils = new PacketUtils(this->jvm, this->listUtils);

}

MessageApiTransformation::~MessageApiTransformation()
{
    try
    {
        delete this->transformationUtils;
        delete this->recordUtils;
        delete this->rejectionUtils;
        delete this->fieldUtils;
        delete this->conditionUtils;
        delete this->packetUtils;
        delete this->listUtils;
        delete this->mapUtils;
        delete this->typeUtils;
        this->jvm->DeleteGlobalRef(this->transformation);
        this->jvm->DeleteGlobalRef(this->transformationMap);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

TransformationUtils *MessageApiTransformation::getTransformationUtils()
{
    return this->transformationUtils;
}

RecordUtils *MessageApiTransformation::getRecordUtils()
{
    return this->recordUtils;
}

RejectionUtils *MessageApiTransformation::getRejectionUtils()
{
    return this->rejectionUtils;
}

FieldUtils *MessageApiTransformation::getFieldUtils()
{
    return this->fieldUtils;
}

ConditionUtils *MessageApiTransformation::getConditionUtils()
{
    return this->conditionUtils;
}

PacketUtils *MessageApiTransformation::getPacketUtils()
{
    return this->packetUtils;
}

ListUtils *MessageApiTransformation::getListUtils()
{
    return this->listUtils;
}

MapUtils *MessageApiTransformation::getMapUtils()
{
    return this->mapUtils;
}

TypeUtils *MessageApiTransformation::getTypeUtils()
{
    return this->typeUtils;
}



