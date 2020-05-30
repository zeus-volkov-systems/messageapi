#ifndef _LISTUTILS_H
#define _LISTUTILS_H

#include <jni.h>
#include "messageapi_structs.h"

#ifdef __cplusplus

#include "JniUtils.h"
#include "TypeUtils.h"
#include <stdlib.h>
#include <iostream>

/**
 * This is the header for the ListUtils object class. ListUtils contains a set of methods used for manipulation of Java Lists
 * in C++ or C code. ListUtils is a class to be instantiated so that it remains thread safe for implementors,
 * while being able 
 */
class ListUtils
{

public:
    /* Default constructor for ListUtils */
    ListUtils(JNIEnv *env, TypeUtils *typeUtils);

    /* Default destructor for ListUtils */
    ~ListUtils();

    /* Utility methods */
    struct val_list *createList();
    int getListLength(jobject jList);
    struct string_list *translateStringList(jobject jList);

    /*List Item Retrieval Methods*/
    struct list_item *getItem(struct val_list *list, int index);
    jobject getObjectItem(struct val_list *list, int index);
    int getIntItem(struct val_list *list, int index);
    long getLongItem(struct val_list *list, int index);
    float getFloatItem(struct val_list *list, int index);
    double getDoubleItem(struct val_list *list, int index);
    signed char getByteItem(struct val_list *list, int index);
    const char *getStringItem(struct val_list *list, int index);
    bool getBoolItem(struct val_list *list, int index);
    short getShortItem(struct val_list *list, int index);
    struct val_list *getListItem(struct val_list *list, int index);

    /*List Item Insertion Methods*/
    void addItem(struct val_list *list, struct list_item *item);
    void addObjectItem(struct val_list *list, jobject val);
    void addIntItem(struct val_list *list, int val);
    void addLongItem(struct val_list *list, long val);
    void addFloatItem(struct val_list *list, float val);
    void addDoubleItem(struct val_list *list, double val);
    void addByteItem(struct val_list *list, signed char val);
    void addStringItem(struct val_list *list, const char *val);
    void addBoolItem(struct val_list *list, bool val);
    void addShortItem(struct val_list *list, short val);
    void addListItem(struct val_list *list, struct val_list *val);

    jmethodID createListMethod();
    jmethodID getListSizeMethod();
    jmethodID getListItemMethod();
    jmethodID addListItemMethod();


private:
    JNIEnv *jvm;
    TypeUtils *typeUtils;

    jmethodID createListMethodId;
    jmethodID getListSizeMethodId;
    jmethodID getListItemMethodId;
    jmethodID addListItemMethodId;

    /* Initialization Methods */
    void loadGlobalRefs(JNIEnv *env, TypeUtils *TypeUtils);
    void loadMethodIds();

};

extern "C"
{

#endif

#ifdef __cplusplus
}
#endif

#endif
