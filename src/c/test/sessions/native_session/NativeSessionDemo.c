#include <jni.h>
#include <stdio.h>
#include "messageapi_structs.h"
#include "MessageApiSessionLib.h"

int main(int argc, char **argv)
{
    puts("In our native session demo test!\n");
    puts("Hello, World\n");
    fflush(stdout);

    session *session = createSession("/workspaces/messageapi/resources/test/file-reader-native/manifest.json");

    puts("Successfully created session.");
    fflush(stdout);

    request *request1 = createRequest(session);

    puts("Successfully created a request.");
    fflush(stdout);

    record *record1 = createRequestRecord(session, request1);

    record *record2 = createRequestRecord(session, request1);

    puts("Successfully created a request record.");
    fflush(stdout);

    field *field1 = getField(session, record1, "file-path");

    puts("Successfully retrieved the file-path field from the request record.");
    fflush(stdout);

    setFieldStringVal(session, field1, "/workspaces/messageapi/resources/test/inputs/file-reader/simpletextfile");

    puts(getFieldStringVal(session, field1));
    fflush(stdout);

    puts("Successfully set the field string value for the file-path field from the request record.");
    fflush(stdout);

    record_list *session_records = createRecordList(session);

    addRecord(session, session_records, record1);

    setRequestRecords(session, request1, session_records);

            response *response = submitRequest(session, request1);

    puts("Successfully submitted the request.");
    fflush(stdout);

    puts(getFieldStringVal(session, field1));
    fflush(stdout);

    while (!isComplete(session, response)) {
        //puts("waiting...");
        //fflush(stdout);
    }

    puts("Successfully returned from the request.");
    fflush(stdout);

    puts(getFieldStringVal(session, field1));
    fflush(stdout);

    record_list *records = getResponseRecords(session, response);
    printf("Record count: %d\n", records->count);
    fflush(stdout);

    //releaseSession(session);

    return 0;
}