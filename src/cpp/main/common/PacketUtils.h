
#ifndef _PACKETUTILS_H
#define _PACKETUTILS_H

#include <jni.h>
#include <stdbool.h>
#include "messageapi_structs.h"

#ifdef __cplusplus
#include <iostream>
#include <string>
#include "ListUtils.h"

/**
 * This is the header for the MessageApiPacket class. 
 * A MessageApiPacket is responsible for creation of native C method ID bindings,
 *  
 * @author Ryan Berkheimer
 */
class PacketUtils
{

public:
    /*Default constructor/destructors*/
    PacketUtils(JNIEnv *javaEnv, ListUtils *listUtils);
    ~PacketUtils();

    /*Packet Methods*/
    void setRecords(struct packet *packet, struct record_list *records);
    void addRecord(struct packet *packet, struct record *record);
    void addRecords(struct packet *packet, struct record_list *records);
    void setRejections(struct packet *packet, struct rejection_list *rejections);
    void addRejection(struct packet *packet, struct rejection *rejection);
    void addRejections(struct packet *packet, struct rejection_list *rejections);
    struct record_list *getRecords(struct packet *packet);
    struct rejection_list *getRejections(struct packet *packet);

private:
    /*Vars*/
    JNIEnv *jvm;
    ListUtils *listUtils;

    /*Packet Methods*/
    jmethodID setRecordsMethodId;
    jmethodID addRecordMethodId;
    jmethodID addRecordsMethodId;
    jmethodID setRejectionsMethodId;
    jmethodID addRejectionMethodId;
    jmethodID addRejectionsMethodId;
    jmethodID getRecordsMethodId;
    jmethodID getRejectionsMethodId;

    /*Load method IDS for reuse. MethodIDS do not count against the jref count and do need to be released.*/
    void loadMethodIds();
    void loadGlobalRefs(JNIEnv *env, ListUtils *listUtils);

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
