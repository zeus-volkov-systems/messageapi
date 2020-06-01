#ifndef _Included_MessageApiTransformation
#define _Included_MessageApiTransformation

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>

#include "JniUtils.h"
#include "MapUtils.h"
#include "ListUtils.h"
#include "TransformationUtils.h"
#include "RecordUtils.h"
#include "RejectionUtils.h"
#include "FieldUtils.h"
#include "ConditionUtils.h"
#include "PacketUtils.h"

/**
 * This is the header for the MessageApiTransformation class - this class is the native side facility
 * for doing transformation processing and communicating back with the java side. This class holds
 * three private vars - a pointer to the jvm where the call originated from, a pointer to the
 * transformation class instance (jobject), and a pointer to the map that holds data for
 * this transformation to process as a jobject. 
 * 
 * The map contains keys that each hold a list of records. These records are immutable, meaning
 * they can be modified however necessary without affecting other transformations or other threads
 * within the computation.
 * 
 * To the user of the MessageApiTransformation library in the native side,
 * they will see the entire library as a single jlong. This jlong holds a pointer to this class,
 * making it easier for implementors to ignore most of the details of implementation.
 * @author Ryan Berkheimer
 */
class MessageApiTransformation
{

public:
    /*Default constructor/destructors*/
    MessageApiTransformation(JNIEnv* javaEnv, jobject jTransformation, jobject jTransformationMap);
    ~MessageApiTransformation();

    /*Utils Accessors*/
    TransformationUtils *getTransformationUtils();
    RecordUtils *getRecordUtils();
    RejectionUtils *getRejectionUtils();
    FieldUtils *getFieldUtils();
    ConditionUtils *getConditionUtils();
    PacketUtils *getPacketUtils();
    ListUtils *getListUtils();
    MapUtils *getMapUtils();
    TypeUtils *getTypeUtils();

private :
    /*Global References*/
    JNIEnv *jvm;
    jobject transformation;
    jobject transformationMap;
    
    TransformationUtils *transformationUtils;
    RecordUtils *recordUtils;
    RejectionUtils *rejectionUtils;
    FieldUtils *fieldUtils;
    ConditionUtils *conditionUtils;
    PacketUtils *packetUtils;
    TypeUtils *typeUtils;
    ListUtils *listUtils;
    MapUtils *mapUtils;

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
