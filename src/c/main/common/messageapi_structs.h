/**
The IField is a basic value-holding type.
The specific type should map to the Java IField.
Which value is set depends on the type, i.e.,
if the type is 'string', stringValue will be set.

The methods that IField supports are
char* messageapi_field_getId(IField);
void messageapi_field_setId(char *id);

 */
struct IField
{
    char *id;
    char *type;
    bool required;
    bool valid;
    bool booleanVal;
    float floatValue;
    double doubleVal;
    int integerValue;
    char *stringValue;
};

/**
The IRecord is an object type that holds a list
of IFields (double pointer).
The methods that IRecord supports are:

 */
struct IRecord
{
    IField **fields;
};

/**
 * 
 */
struct IRejection
{
    IRecord *record;
    char **reasons;
};

/**
The IPacket is an object type that holds
a list of records and a list of rejections.
 */
struct IPacket
{
    IRecord **records;
    IRejection **rejections;
};