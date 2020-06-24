#include <jni.h>
#include <stdio.h>
#include "messageapi_structs.h"

int main(int argc, char **argv)
{
    printf("In our native session demo test!\n");
    printf("Hello, World\n");
    fflush(stdout);

    //session *session = createSession("/Users/rberkheimer/projects/asos/ingest/libraries/messageapi/resources/test/file-reader/manifest.json");

    printf("Successfully created session.");
    fflush(stdout);

    return 0;
}