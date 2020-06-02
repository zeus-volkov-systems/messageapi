#include "MessageApiSessionLib.h"

extern "C"
{
    /**
 * Creates the default session.
 */
    session *createSession(const char *spec)
    {
        session *session;
        JavaVM *vm;
        JNIEnv *env;
        JavaVMInitArgs vm_args;

        jint jvmCreationStatus = JNI_CreateJavaVM(&vm, (void **)&env, &vm_args);
        if (jvmCreationStatus != JNI_OK)
        {
            printf("Failed to create Java VM\n");
            fflush(stdout);
            return NULL;
        }

        jclass sessionClass = JniUtils::getNamedClass(env, "gov/noaa/messageapi/sessions/DefaultSession");
        jmethodID createSessionMethodId = JniUtils::getMethod(env, sessionClass, "<init>", "(Ljava/lang/String;)V", false);
        jstring jSpec = env->NewStringUTF(spec);
        jobject jSession = env->NewObject(sessionClass, createSessionMethodId);
        jlong sessionLib = reinterpret_cast<jlong>(new MessageApiSession(env, jSession));
        struct session *session = (struct session *)malloc(sizeof(session) + sizeof(sessionLib));
        session->sessionLib = sessionLib;
        env->DeleteLocalRef(jSession);
        env->DeleteLocalRef(jSpec);
        env->DeleteLocalRef(sessionClass);
        return session;
    }

    /**
    * Deletes the C++ pointer (calls C++ destructor)) that references the object created during session construction.
    * This call is NOT made automatically, as the session is created Natively, so this should be called manually.
    */
    void releaseSession(session *session)
    {
        delete reinterpret_cast<MessageApiSession *>(session->sessionLib);
        free(session);
    }

    request *createRequest(session *session)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getSessionUtils()->createRequest();
    }

    /* Request methods */
    record *createRequestRecord(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->createRecord(request);
    }

    request *getRequestCopy(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->getCopy(request);
    }

    request *getRequestCopyComponents(session *session, request *request, val_list *copy_components)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->getCopy(request, copy_components);
    }

    const char *getRequestType(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->getType(request);
    }

    record_list *getRequestRecords(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->getRecords(request);
    }

    record *getRequestRecord(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->getRequestRecord(request);
    }

    void setRequestRecords(session *session, request *request, record_list *records)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->setRecords(request, records);
    }

    response *submitRequest(session *session, request *request)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRequestUtils()->submitRequest(request);
    }

    /* Response methods */
    bool isComplete(session *session, response *response)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->isComplete(response);
    }

    request *getResponseRequest(session *session, response *response)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->getRequest(response);
    }

    rejection_list *getResponseRejections(session *session, response *response)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->getRejections(response);
    }

    record_list *getResponseRecords(session *session, response *response)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->getRecords(response);
    }

    void setResponseRejections(session *session, response *response, rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->setRejections(response, rejections);
    }

    void setResponseRecords(session *session, response *response, record_list *records)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->setRecords(response, records);
    }

    void setComplete(session *session, response *response, bool isComplete)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getResponseUtils()->setComplete(response, isComplete);
    }

    record_list *createRecordList(session *session)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->createRecordList();
    }

    void addRecord(session *session, record_list *record_list, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->addRecord(record_list, record);
    }

    record *getRecord(session *session, record_list *recordList, int recordIndex)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getRecord(recordList, recordIndex);
    }

    record *getRecordCopy(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getCopy(record);
    }

    bool getRecordIsValid(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->isValid(record);
    }

    string_list *getFieldIds(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getFieldIds(record);
    }

    field_list *getFields(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getFields(record);
    }

    field *getField(session *session, record *record, const char* fieldId)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getField(record, fieldId);
    }

    bool hasField(session *session, record *record, const char *fieldId)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->hasField(record, fieldId);
    }

    string_list *getConditionIds(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getConditionIds(record);
    }

    condition_list *getConditions(session *session, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getConditions(record);
    }

    condition *getCondition(session *session, record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->getCondition(record, conditionId);
    }

    bool hasCondition(session *session, record *record, const char *conditionId)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRecordUtils()->hasCondition(record, conditionId);
    }

    /*Field Methods*/

    const char *getFieldId(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getId(field);
    }

    const char *getFieldType(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getType(field);
    }

    bool getFieldIsValid(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->isValid(field);
    }

    bool getFieldIsRequired(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->isRequired(field);
    }

    bool getFieldIsNull(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->isNull(field);
    }

    val *getFieldVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getVal(field);
    }

    int getFieldIntVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getIntVal(field);
    }

    long getFieldLongVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getLongVal(field);
    }

    float getFieldFloatVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getFloatVal(field);
    }

    double getFieldDoubleVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getDoubleVal(field);
    }

    signed char getFieldByteVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getByteVal(field);
    }

    const char *getFieldStringVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getStringVal(field);
    }

    bool getFieldBoolVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getBoolVal(field);
    }

    short getFieldShortVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getShortVal(field);
    }

    val_list *getFieldListVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getListVal(field);
    }

    val_map *getFieldMapVal(session *session, field *field)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->getMapVal(field);
    }

    void setFieldVal(session *session, field *field, val *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setVal(field, value);
    }

    void setFieldIntVal(session *session, field *field, int value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setIntVal(field, value);
    }

    void setFieldLongVal(session *session, field *field, long value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setLongVal(field, value);
    }

    void setFieldFloatVal(session *session, field *field, float value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setFloatVal(field, value);
    }

    void setFieldDoubleVal(session *session, field *field, double value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setDoubleVal(field, value);
    }

    void setFieldByteVal(session *session, field *field, signed char value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setByteVal(field, value);
    }

    void setFieldStringVal(session *session, field *field, const char *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setStringVal(field, value);
    }

    void setFieldBoolVal(session *session, field *field, bool value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setBoolVal(field, value);
    }

    void setFieldShortVal(session *session, field *field, short value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setShortVal(field, value);
    }

    void setFieldListVal(session *session, field *field, val_list *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setListVal(field, value);
    }

    void setFieldMapVal(session *session, field *field, val_map *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getFieldUtils()->setMapVal(field, value);
    }

    /*Condition Methods*/

    const char *getConditionId(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getId(condition);
    }

    const char *getConditionType(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getType(condition);
    }

    const char *getConditionOperator(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getOperator(condition);
    }

    bool getConditionIsNull(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->isNull(condition);
    }

    val *getConditionVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getVal(condition);
    }
    
    int getConditionIntVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getIntVal(condition);
    }

    long getConditionLongVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getLongVal(condition);
    }

    float getConditionFloatVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getFloatVal(condition);
    }

    double getConditionDoubleVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getDoubleVal(condition);
    }

    signed char getConditionByteVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getByteVal(condition);
    }

    const char *getConditionStringVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getStringVal(condition);
    }

    bool getConditionBoolVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getBoolVal(condition);
    }

    short getConditionShortVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getShortVal(condition);
    }

    val_list *getConditionListVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getListVal(condition);
    }

    val_map *getConditionMapVal(session *session, condition *condition)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->getMapVal(condition);
    }

    void setConditionVal(session *session, condition *condition, val *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setVal(condition, value);
    }

    void setConditionIntVal(session *session, condition *condition, int value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setIntVal(condition, value);
    }

    void setConditionLongVal(session *session, condition *condition, long value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setLongVal(condition, value);
    }

    void setConditionFloatVal(session *session, condition *condition, float value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setFloatVal(condition, value);
    }

    void setConditionDoubleVal(session *session, condition *condition, double value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setDoubleVal(condition, value);
    }

    void setConditionByteVal(session *session, condition *condition, signed char value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setByteVal(condition, value);
    }

    void setConditionStringVal(session *session, condition *condition, const char *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setStringVal(condition, value);
    }

    void setConditionBoolVal(session *session, condition *condition, bool value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setBoolVal(condition, value);
    }

    void setConditionShortVal(session *session, condition *condition, short value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setShortVal(condition, value);
    }

    void setConditionListVal(session *session, condition *condition, val_list *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setListVal(condition, value);
    }

    void setConditionMapVal(session *session, condition *condition, val_map *value)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getConditionUtils()->setMapVal(condition, value);
    }

    /*List Utility Methods*/

    list_item *getItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getItem(list, index);
    }

    val_list *getListItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getListItem(list, index);
    }

    val_map *getMapItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getMapItem(list, index);
    }

    int getIntItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getIntItem(list, index);
    }

    long getLongItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getLongItem(list, index);
    }

    float getFloatItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getFloatItem(list, index);
    }

    double getDoubleItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getDoubleItem(list, index);
    }

    signed char getByteItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getByteItem(list, index);
    }

    const char *getStringItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getStringItem(list, index);
    }

    bool getBoolItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getBoolItem(list, index);
    }

    short getShortItem(session *session, val_list *list, int index)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->getShortItem(list, index);
    }

    val_list *createList(session *session)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->createList();
    }

    void addItem(session *session, val_list *list, list_item *item)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addItem(list, item);
    }

    void addIntItem(session *session, val_list *list, int val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addIntItem(list, val);
    }

    void addLongItem(session *session, val_list *list, long val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addLongItem(list, val);
    }

    void addFloatItem(session *session, val_list *list, float val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addFloatItem(list, val);
    }

    void addDoubleItem(session *session, val_list *list, double val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addDoubleItem(list, val);
    }

    void addByteItem(session *session, val_list *list, signed char val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addByteItem(list, val);
    }

    void addStringItem(session *session, val_list *list, const char *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addStringItem(list, val);
    }

    void addBoolItem(session *session, val_list *list, bool val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addBoolItem(list, val);
    }

    void addShortItem(session *session, val_list *list, short val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addShortItem(list, val);
    }

    void addListItem(session *session, val_list *list, val_list *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addListItem(list, val);
    }

    void addMapItem(session *session, val_list *list, val_map *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getListUtils()->addMapItem(list, val);
    }

    /*Map Utility Methods*/
    val_map *createMap(session *session)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->createMap();
    }

    int getSize(session *session, val_map *map)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getSize(map);
    }

    bool hasKey(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->hasKey(map, key);
    }

    /*Map Value Retrieval Methods*/
    map_val *getVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getVal(map, key);
    }

    jobject getObjectVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getObjectVal(map, key);
    }

    int getIntVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getIntVal(map, key);
    }

    long getLongVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getLongVal(map, key);
    }

    float getFloatVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getFloatVal(map, key);
    }

    double getDoubleVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getDoubleVal(map, key);
    }

    signed char getByteVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getByteVal(map, key);
    }

    const char *getStringVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getStringVal(map, key);
    }

    bool getBoolVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getBoolVal(map, key);
    }

    short getShortVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getShortVal(map, key);
    }

    val_list *getListVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getListVal(map, key);
    }

    val_map *getMapVal(session *session, val_map *map, const char *key)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->getMapVal(map, key);
    }

    /*Insert or Update Methods*/
    void putVal(session *session, val_map *map, const char *key, map_val *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putVal(map, key, val);
    }

    void putObjectVal(session *session, val_map *map, const char *key, jobject val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putObjectVal(map, key, val);
    }

    void putIntVal(session *session, val_map *map, const char *key, int val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putIntVal(map, key, val);
    }

    void putLongVal(session *session, val_map *map, const char *key, long val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putLongVal(map, key, val);
    }

    void putFloatVal(session *session, val_map *map, const char *key, float val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putFloatVal(map, key, val);
    }

    void putDoubleVal(session *session, val_map *map, const char *key, double val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putDoubleVal(map, key, val);
    }

    void putByteVal(session *session, val_map *map, const char *key, signed char val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putByteVal(map, key, val);
    }

    void putStringVal(session *session, val_map *map, const char *key, const char *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putStringVal(map, key, val);
    }

    void putBoolVal(session *session, val_map *map, const char *key, bool val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putBoolVal(map, key, val);
    }

    void putShortVal(session *session, val_map *map, const char *key, short val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putShortVal(map, key, val);
    }

    void putListVal(session *session, val_map *map, const char *key, val_list *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putListVal(map, key, val);
    }

    void putMapVal(session *session, val_map *map, const char *key, val_map *val)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getMapUtils()->putMapVal(map, key, val);
    }

    /*Rejection Utils*/
    rejection_list *createRejectionList(session *session)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->createRejectionList();
    }

    void addRejection(session *session, rejection_list *rejection_list, rejection *rejection)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->addRejection(rejection_list, rejection);
    }

    rejection *getRejectionCopy(session *session, rejection *rejection)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->getCopy(rejection);
    }

    record *getRejectionRecord(session *session, rejection *rejection)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->getRecord(rejection);
    }

    string_list *getRejectionReasons(session *session, rejection *rejection)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->getReasons(rejection);
    }

    void addRejectionReason(session *session, rejection *rejection, const char *reason)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getRejectionUtils()->addReason(rejection, reason);
    }

    /*Packet Utils*/
    void addPacketRecord(session *session, packet *packet, record *record)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->addRecord(packet, record);
    }

    void setPacketRecords(session *session, packet *packet, record_list *records)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->setRecords(packet, records);
    }

    void addPacketRecords(session *session, packet *packet, record_list *records)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->addRecords(packet, records);
    }

    void setPacketRejections(session *session, packet *packet, rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->setRejections(packet, rejections);
    }

    void addPacketRejection(session *session, packet *packet, rejection *rejection)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->addRejection(packet, rejection);
    }

    void addPacketRejections(session *session, packet *packet, rejection_list *rejections)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->addRejections(packet, rejections);
    }

    record_list *getPacketRecords(session *session, packet *packet)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->getRecords(packet);
    }

    rejection_list *getPacketRejections(session *session, packet *packet)
    {
        return reinterpret_cast<MessageApiSession *>(session->sessionLib)->getPacketUtils()->getRejections(packet);
    }
}