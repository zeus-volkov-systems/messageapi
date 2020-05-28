#include "RecordUtils.h"

#include <jni.h>


/**
Constructor for the RecordUtils object.
*/
RecordUtils::RecordUtils(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->loadGlobalRefs(jvm, typeUtils, listUtils);
    this->loadMethodIds();
}

RecordUtils::~RecordUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/*Public API*/

bool RecordUtils::isValid(struct record *record)
{
    return (bool)this->jvm->CallBooleanMethod(record->jrecord, this->isValidMethodId);
}

struct record *RecordUtils::getCopy(struct record *record)
{
    jobject jRecordCopy = this->jvm->CallObjectMethod(record->jrecord, this->getCopyMethodId);
    struct record *recordCopy = (struct record *)malloc(sizeof(struct record) + sizeof(jRecordCopy));
    recordCopy->jrecord = jRecordCopy;
    return recordCopy;
}

bool RecordUtils::hasField(struct record *record, const char *fieldId)
{
    jstring jFieldId = this->typeUtils->toJavaString(fieldId);
    bool hasJField = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->hasFieldMethodId, jFieldId);
    this->jvm->DeleteLocalRef(jFieldId);
    return hasJField;
}
struct string_list *RecordUtils::getFieldIds(struct record *record)
{
    jobject jFieldIdList = this->jvm->CallObjectMethod(record->jrecord, this->getFieldIdsMethodId);
    struct string_list *field_ids = this->listUtils->translateStringList(jFieldIdList);
    this->jvm->DeleteLocalRef(jFieldIdList);
    return field_ids;
}
struct field_list *RecordUtils::getFields(struct record *record)
{
    jobject jFieldList = this->jvm->CallObjectMethod(record->jrecord, this->getFieldsMethodId);

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

struct field *RecordUtils::getField(struct record *record, const char *fieldId)
{
    jstring jFieldId = this->typeUtils->toJavaString(fieldId);
    jobject jField = this->jvm->CallObjectMethod(record->jrecord, this->getFieldMethodId, jFieldId);
    struct field *field = (struct field *)malloc(sizeof(struct field) + sizeof(jField));
    field->jfield = jField;
    this->jvm->DeleteLocalRef(jFieldId);
    return field;
}

bool RecordUtils::hasCondition(struct record *record, const char *conditionId)
{
    jstring jConditionId = this->typeUtils->toJavaString(conditionId);
    bool hasJCondition = (bool)this->jvm->CallBooleanMethod(record->jrecord, this->hasConditionMethodId, jConditionId);
    this->jvm->DeleteLocalRef(jConditionId);
    return hasJCondition;
}

struct string_list *RecordUtils::getConditionIds(struct record *record)
{
    jobject jConditionIdList = this->jvm->CallObjectMethod(record->jrecord, this->getConditionIdsMethodId);
    struct string_list *condition_ids = this->listUtils->translateStringList(jConditionIdList);
    this->jvm->DeleteLocalRef(jConditionIdList);
    return condition_ids;
}

struct condition_list *RecordUtils::getConditions(struct record *record)
{
    jobject jConditionList = this->jvm->CallObjectMethod(record->jrecord, this->getConditionsMethodId);

    int conditionCount = this->listUtils->getListLength(jConditionList);
    struct condition **conditions = (struct condition **)malloc(sizeof(struct condition *) * conditionCount);

    for (int i = 0; i < conditionCount; i++)
    {
        jobject jcondition = static_cast<jobject>(this->jvm->CallObjectMethod(jConditionList, this->listUtils->getListItemMethod(), i));
        struct condition *condition = (struct condition *)malloc(sizeof(condition) + sizeof(jcondition));
        condition->jcondition = (jobject)jcondition;
        conditions[i] = condition;
    }

    struct condition_list *condition_list = (struct condition_list *)malloc(sizeof(struct condition_list) + sizeof(conditions));
    condition_list->count = conditionCount;
    condition_list->conditions = conditions;
    return condition_list;
}

struct condition *RecordUtils::getCondition(struct record *record, const char *conditionId)
{
    jstring jConditionId = this->typeUtils->toJavaString(conditionId);
    jobject jCondition = this->jvm->CallObjectMethod(record->jrecord, this->getConditionMethodId, jConditionId);
    struct condition *condition = (struct condition *)malloc(sizeof(struct condition) + sizeof(jCondition));
    condition->jcondition = jCondition;
    this->jvm->DeleteLocalRef(jConditionId);
    return condition;
}

struct record_list *RecordUtils::createRecordList()
{
    jobject jList = this->jvm->NewObject(this->typeUtils->getListClass(), this->listUtils->createListMethod());
    struct record_list *record_list = (struct record_list *)malloc(sizeof(struct record_list));
    record_list->count = 0;
    record_list->jrecords = jList;
    return record_list;
}

void RecordUtils::addRecord(struct record_list *record_list, struct record *record)
{
    this->jvm->CallVoidMethod(record_list->jrecords, this->listUtils->addListItemMethod(), record->jrecord);
    record_list->count += 1;
}

struct record *RecordUtils::getRecord(struct record_list *record_list, int index)
{
    jobject jrecord = this->jvm->CallObjectMethod(record_list->jrecords, this->listUtils->getListItemMethod(), index);
    struct record *record = (struct record *)malloc(sizeof(struct record) + sizeof(jrecord));
    record->jrecord = jrecord;
    return record;
}

/*Private methods*/

void RecordUtils::loadGlobalRefs(JNIEnv *jvm, TypeUtils *typeUtils, ListUtils *listUtils)
{
    this->jvm = jvm;
    this->typeUtils = typeUtils;
    this->listUtils = listUtils;
}

void RecordUtils::loadMethodIds()
{
    jclass recordClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/IRecord");
    /*Intrinsic Methods*/
    this->isValidMethodId = JniUtils::getMethod(this->jvm, recordClass, "isValid", this->getMethodSignature("isValid"), false);
    this->getCopyMethodId = JniUtils::getMethod(this->jvm, recordClass, "getCopy", this->getMethodSignature("getCopy"), false);
    /*Field Related Methods*/
    this->getFieldIdsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getFieldIds", this->getMethodSignature("getFieldIds"), false);
    this->getFieldsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getFields", this->getMethodSignature("getFields"), false);
    this->hasFieldMethodId = JniUtils::getMethod(this->jvm, recordClass, "hasField", this->getMethodSignature("hasField"), false);
    this->getFieldMethodId = JniUtils::getMethod(this->jvm, recordClass, "getField", this->getMethodSignature("getField"), false);
    /*Condition Related Methods*/
    this->getConditionIdsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getConditionIds", this->getMethodSignature("getConditionIds"), false);
    this->getConditionsMethodId = JniUtils::getMethod(this->jvm, recordClass, "getConditions", this->getMethodSignature("getConditions"), false);
    this->hasConditionMethodId = JniUtils::getMethod(this->jvm, recordClass, "hasCondition", this->getMethodSignature("hasCondition"), false);
    this->getConditionMethodId = JniUtils::getMethod(this->jvm, recordClass, "getCondition", this->getMethodSignature("getCondition"), false);
    this->jvm->DeleteLocalRef(recordClass);
}

const char *RecordUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "isValid") == 0)
    {
        return "()Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getCopy") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRecord;";
    }
    else if (strcmp(methodName, "getFieldIds") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "hasField") == 0)
    {
        return "(Ljava/lang/String;)Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getFields") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getField") == 0)
    {
        return "(Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/IField;";
    }
    else if (strcmp(methodName, "getConditionIds") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "hasCondition") == 0)
    {
        return "(Ljava/lang/String;)Ljava/lang/Boolean;";
    }
    else if (strcmp(methodName, "getConditions") == 0)
    {
        return "()Ljava/util/List;";
    }
    else if (strcmp(methodName, "getCondition") == 0)
    {
        return "(Ljava/lang/String;)Lgov/noaa/messageapi/interfaces/ICondition;";
    }
    return NULL;
}
