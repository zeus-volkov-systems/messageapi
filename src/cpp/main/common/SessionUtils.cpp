#include "SessionUtils.h"

#include <jni.h>

/**
 * Sessions are the top level API container of any given computation. Sessions
 * bootstrap from a specification map and 'lock-in' a computation environment,
 * allowing requests to be created.
 * 
 * @author Ryan Berkheimer
 */

/* Default Constructor */
SessionUtils::SessionUtils(JNIEnv *jvm, jobject session)
{
    this->loadGlobalRefs(jvm, session);
    this->loadMethodIds();
}

/* Default Destructor */
SessionUtils::~SessionUtils()
{
    try
    {}
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }
}

/* Public API */

struct request *SessionUtils::createRequest()
{
    jobject jrequest = this->jvm->CallObjectMethod(this->session, this->createRequestMethodId);
    struct request *request = (struct request *)malloc(sizeof(struct request) + sizeof(jrequest));
    request->jrequest = jrequest;
    return request;
}

/* Private Methods */

void SessionUtils::loadGlobalRefs(JNIEnv *jvm, jobject session)
{
    this->jvm = jvm;
    this->session = session;
}

void SessionUtils::loadMethodIds()
{
    jclass sessionClass = JniUtils::getNamedClass(this->jvm, "gov/noaa/messageapi/interfaces/ISession");

    this->createRequestMethodId = JniUtils::getMethod(this->jvm, sessionClass, "createRequest", this->getMethodSignature("createRequest"), false);

    jvm->DeleteLocalRef(sessionClass);
}


const char *SessionUtils::getMethodSignature(const char *methodName)
{
    if (strcmp(methodName, "createRequest") == 0)
    {
        return "()Lgov/noaa/messageapi/interfaces/IRequest;";
    }
    return NULL;
}