#include "ListUtils.h"

ListUtils::ListUtils(JNIEnv *env, TypeUtils *typeUtils)
{
    this->loadGlobalRefs(env, typeUtils);
    this->loadMethodIds();
}

ListUtils::~ListUtils()
{
    try
    {
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

void ListUtils::loadGlobalRefs(JNIEnv *env, TypeUtils *typeUtils)
{
    this->jvm = env;
    this->typeUtils = typeUtils;
}

void ListUtils::loadMethodIds()
{
    jclass listClass = JniUtils::getNamedClass(this->jvm, "java/util/List");
    this->getListSizeMethodId = this->jvm->GetMethodID(listClass, "size", "()I");
    this->getListItemMethodId = this->jvm->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    this->addListItemMethodId = this->jvm->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    this->jvm->DeleteLocalRef(listClass);

    this->createListMethodId = this->jvm->GetMethodID(this->typeUtils->getListClass(), "<init>", "()V");
}

jmethodID ListUtils::createListMethod()
{
    return this->createListMethodId;
}

jmethodID ListUtils::getListSizeMethod()
{
    return this->getListSizeMethodId;
}

jmethodID ListUtils::getListItemMethod()
{
    return this->getListItemMethodId;
}

jmethodID ListUtils::addListItemMethod()
{
    return this->addListItemMethodId;
}

struct val_list *ListUtils::createList()
{
    jobject jList = this->jvm->NewObject(this->typeUtils->getListClass(), this->createListMethod());
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = 0;
    valueList->jlist = jList;
    return valueList;
}

int ListUtils::getListLength(jobject jList)
{
    return (int)this->jvm->CallIntMethod(jList, this->getListSizeMethod());
}

struct list_item *ListUtils::getItem(struct val_list *list, int index)
{
    struct list_item *listItem = (struct list_item *)malloc(sizeof(struct list_item));
    listItem->jitem = this->getObjectItem(list, index);
    return listItem;
}

jobject ListUtils::getObjectItem(struct val_list *val_list, int index)
{
    return static_cast<jobject>(this->jvm->CallObjectMethod(val_list->jlist, this->getListItemMethod(), index));
}

struct val_list *ListUtils::getListItem(struct val_list *list, int index)
{
    jobject listItem = this->getObjectItem(list, index);
    int itemCount = this->getListLength(listItem);
    struct val_list *valueList = (struct val_list *)malloc(sizeof(struct val_list));
    valueList->count = itemCount;
    valueList->jlist = listItem;
    return valueList;
}

struct val_map *ListUtils::getMapItem(struct val_list *list, int index)
{
    jobject mapItem = this->getObjectItem(list, index);
    struct val_map *valMap = (struct val_map *)malloc(sizeof(struct val_map));
    valMap->jmap = mapItem;
    return valMap;
}

int ListUtils::getIntItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    int val = (int)this->jvm->CallIntMethod(list_item, this->typeUtils->getIntMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

long ListUtils::getLongItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    long val = (long)this->jvm->CallLongMethod(list_item, this->typeUtils->getLongMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

float ListUtils::getFloatItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    float val = (float)this->jvm->CallFloatMethod(list_item, this->typeUtils->getFloatMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

double ListUtils::getDoubleItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    double val = (double)this->jvm->CallDoubleMethod(list_item, this->typeUtils->getDoubleMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

signed char ListUtils::getByteItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    signed char val = (signed char)this->jvm->CallByteMethod(list_item, this->typeUtils->getByteMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

const char *ListUtils::getStringItem(struct val_list *list, int index)
{
    jstring jString = static_cast<jstring>(this->jvm->CallObjectMethod(list->jlist, this->getListItemMethod(), index));
    const char *val = this->typeUtils->fromJavaString(jString);
    jvm->DeleteLocalRef(jString);
    return val;
}

bool ListUtils::getBoolItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    bool val = (bool)this->jvm->CallBooleanMethod(list_item, this->typeUtils->getBoolMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

short ListUtils::getShortItem(struct val_list *list, int index)
{
    jobject list_item = this->getObjectItem(list, index);
    short val = (short)this->jvm->CallShortMethod(list_item, this->typeUtils->getShortMethod());
    jvm->DeleteLocalRef(list_item);
    return val;
}

void ListUtils::addObjectItem(struct val_list *list, jobject val)
{
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), val);
    list->count += 1;
}

void ListUtils::addItem(struct val_list *list, struct list_item *item)
{
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), item->jitem);
    list->count += 1;
}

void ListUtils::addIntItem(struct val_list *list, int val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getIntClass(), this->typeUtils->createIntMethod(), (jint)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addLongItem(struct val_list *list, long val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getLongClass(), this->typeUtils->createLongMethod(), (jlong)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addFloatItem(struct val_list *list, float val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getFloatClass(), this->typeUtils->createFloatMethod(), (jfloat)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addDoubleItem(struct val_list *list, double val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getDoubleClass(), this->typeUtils->createDoubleMethod(), (jdouble)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addByteItem(struct val_list *list, signed char val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getByteClass(), this->typeUtils->createByteMethod(), (jbyte)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addStringItem(struct val_list *list, const char *val)
{
    jstring jVal = this->typeUtils->toJavaString(val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addBoolItem(struct val_list *list, bool val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getBoolClass(), this->typeUtils->createBoolMethod(), (jboolean)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addShortItem(struct val_list *list, short val)
{
    jobject jVal = jvm->NewObject(this->typeUtils->getShortClass(), this->typeUtils->createShortMethod(), (jshort)val);
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), jVal);
    list->count += 1;
    this->jvm->DeleteLocalRef(jVal);
}

void ListUtils::addListItem(struct val_list *list, struct val_list *val)
{
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), val->jlist);
    list->count += 1;
}

void ListUtils::addMapItem(struct val_list *list, struct val_map *val)
{
    this->jvm->CallVoidMethod(list->jlist, this->addListItemMethod(), val->jmap);
    list->count += 1;
}

struct string_list *ListUtils::translateStringList(jobject jList)
{
    int stringCount = this->getListLength(jList);
    char **strings = (char **)malloc(sizeof(char *) * stringCount);
    int maxStringLength = 0;
    for (int i = 0; i < stringCount; i++)
    {
        jstring jString = static_cast<jstring>(this->jvm->CallObjectMethod(jList, this->getListItemMethod(), i));
        const char *tempString = this->jvm->GetStringUTFChars(jString, NULL);
        int tempMaxStringLength = strlen(tempString);
        if (tempMaxStringLength > maxStringLength)
        {
            maxStringLength = tempMaxStringLength;
        }
        strings[i] = (char *)malloc((tempMaxStringLength + 1) * sizeof(char));
        strcpy(strings[i], tempString);
        this->jvm->ReleaseStringUTFChars(jString, tempString);
        this->jvm->DeleteLocalRef(jString);
    }

    struct string_list *string_list = (struct string_list *)malloc(sizeof(struct string_list) + sizeof(strings));
    string_list->count = stringCount;
    string_list->max_length = maxStringLength;
    string_list->strings = strings;
    return string_list;
}
