/**
This header contains the definitions
for all structs used by the native messageAPI
library.
These structs correspond to the interfaces
available for interaction in the Java portion
of the library. These structs should not
ever need to change - any native library
should be able to completely interact with
MessageAPI.

The struct surface consists of:

-field
-condition
-record
-rejection
-request
-response
-packet
-session

@author Ryan Berkheimer
*/

/**
The field is a basic value-holding struct.
It should only hold one 'type' of value.
The value methods associated with this struct
operate on void pointers and must be cast
by the caller depending on the 'type' property
of the field.

The library methods that the field struct is related to are

char* messageapi_field_getId(field *f);
char* messageapi_field_getType(field *f);
void* messageapi_field_getValue(field *f);

bool messageapi_field_isRequired(field *f);
bool messageapi_field_isValid(field *f);

bool messageapi_field_setValid(field *f, bool isValid);
void messageapi_field_setType(field* f, char *type);
void messageapi_field_setValue(field *f, void *value);

 */
struct field
{
    char *id;
    char *type;
    bool isRequired;
    bool isValid;
    void *value;
};

/**
The condition is used in filtering,
belonging to both records and requests.
Conditions are defined outside of code,
with values being able to be set inside
or outside of code. Like Fields, conditions
define a specific type that is used in validation on
value assignment. Values are both set and retrieved
as void pointers, so must be cast by the user based on
the type.

char* messageapi_condition_getId(condition *c);
char* messageapi_condition_getType(condition *c);
char* messageapi_condition_getOperator(condition *c);
void* messageapi_condition_getValue(condition *c);

char* messageapi_condition_setValue(condition *c, void *value);
 */
struct condition
{
    char *id;
    char *type;
    char *oprtr;
    void *value;
};

/**
The record struct holds a list
of fields and a list of conditions, and a
boolean indicating if the record is valid or not.
The record is related to several library methods that
provide access to its members, along with another
method that allows getting a full copy of the record.

The library methods that record relates to are:

field** messageapi_record_getFields(record *r);
field* messageapi_record_getField(record *r, char* fieldId);
bool messageapi_record_hasField(record *r, char* fieldId);

condition** messageapi_record_getConditions(record *r);
condition* messageapi_record_getCondition(record *r, char* conditionId);

record* messageapi_record_getCopy(record *r);

void messageapi_record_setFields(record *r, field** fields);
void messageapi_record_setField(record *r, void* field, void* value);

void messageapi_record_setConditions(record *r, condition** conditions);
void messageapi_record_setCondition(record *r, void* condition, void* value);

bool messageapi_record_isValid(record *r);
void messageapi_record_setValid(record *r, bool valid);
 */
struct record
{
    field **fields;
    condition **conditions;
    bool isValid;
};

/**
The rejection struct holds a reference to the record
that was rejected, and a list of reasons as strings
that explain why the referenced record was rejected.

Library methods that relate to rejections include:

record* messageapi_rejection_getRecord(rejection* r);

rejection* messageapi_rejection_getCopy(rejection* r);

char** messageapi_rejection_getReasons(rejection* r);
void messageapi_rejection_addReason(rejection* r, char* reason);
 */
struct rejection
{
    record *record;
    char **reasons;
};

/**
The request struct holds a list of records and its own
request record (which holds request-wide conditions).
Requests, derived from Sessions (holding a deep copy of
the session schema, container, and protocol), are the primary
vector of process formation and execution in MessageAPI.
Requests are submitted directly and immediately return a response
asynchronously. Requests can be reused, with each submit() call
applying to the same endpoint state.

Library methods that relate to requests include:

record* messageapi_request_createRecord(request* r);
request* messageapi_request_getCopy(request* r);
record** messageapi_request_getRecords(request* r);
void messageapi_request_setCondition(char* id, void* value);
void messageapi_request_setRecords(request* request, record** records);
response* messageapi_request_submit(request* r);
 */
struct request
{
    record **records;
    record **requestRecord;
};

/**
The response struct primarily holds
the initiating request, a list of records,
and a list of rejections. It also holds a
boolean value isComplete that specifies
whether or not the processing that takes place
in the response has finished, and that the records
and rejections are available for consumption.

Library methods that relate to responses include:

request* messageapi_response_getRequest(response* r);
bool messageapi_response_isComplete(response* r);
record** messageapi_response_getRecords(response* r);
rejection** messageapi_response_getRejections(response* r);
 */
struct response
{
    request* request;
    bool isComplete;
    record** records;
    rejection** rejections;
};

/**
The packet struct holds a list of records
and a list of rejections. It is used as a
return for all endpoint connections.

Library methods that relate to packets include:

void messageapi_packet_setRecords(packet* p, records** rs);
void messageapi_packet_addRecord(packet* p, record* r);
void messageapi_packet_addRecords(packet* p, record** rs);
record** messageapi_packet_getRecords(packet* p);

void messageapi_packet_setRejections(packet* p, rejections** rs);
void messageapi_packet_addRejection(packet* p, rejection* r);
void messageapi_packet_addRejections(packet* p, rejections** rs);
record** messageapi_packet_getRejections(packet* p);

 */
struct packet
{
    record** records;
    rejection** rejections;
};

/**
The session struct holds the ability to create
requests. It creates these requests using a definition
of a schema, container, and protocol.

Library methods that relate to packets include:

request* messageapi_create_request(const char* sessionManifest);
 */
struct session
{

};
