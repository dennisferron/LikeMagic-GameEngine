
#include "Iocaste/Exception.hpp"

#include "Iocaste/CShims/Exception.h"
#include "IoState.h"

#include "IoObject.h"

#include <iostream>
using namespace std;

using namespace Iocaste;

ScriptException::ScriptException(IoObject* self_) : self(self_), errorText(getErrorText(self_))
{
}

ScriptException::~ScriptException() noexcept(true)
{
}


IoObject* ScriptException::getSelf() const
{
    return self;
}

char const* ScriptException::what() const throw()
{
    return errorText.c_str();
}

std::string ScriptException::getErrorText(IoObject* self)
{
    if (!self)
        return "<<Missing Io Exception object>>";

    // This freezes up if the exception causes destruction of the IoVM object
    // maybe we should just cache the what() message in a string.
	IoObject *msg = IoObject_rawGetSlot_(self, IOSYMBOL("error"));

	if (!msg)
        return "<<Io Exception object has no 'error' slot>>";

	if (!ISSEQ(msg))
        return "<<Io Exception 'error' slot is not a string>>";

    return CSTRING(msg);
}


IoStateError::IoStateError(IoObject* self, std::string description_, IoObject* message_)
    : ScriptException(self), description(description_), message(message_)
{
}

IoStateError::~IoStateError() throw()
{
}

IoObject* IoStateError::getMessage() const
{
    return message;
}

char const* IoStateError::what() const throw()
{
    return description.c_str();
}


extern "C" IoObject *IocasteException_proto(void *state)
{
	IoObject *self = IoObject_new(state);
	IoTag *tag = IoTag_newWithName_("Exception");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoObject_rawClone);
	IoObject_tag_(self, tag);

	IoState_registerProtoWithFunc_((IoState*)state, self, IocasteException_proto);

	{
		IoMethodTable methodTable[] = {
			{"doTry", doTry},
			{"throw", throwScriptException},
			{NULL, NULL}
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}

extern "C" IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m)
{
    // Disambiguating stack frames for this function to try to figure
    // out why CLI try is not catching final exception.
    static int instanceCounter = 0;
    int thisInstance = ++instanceCounter;

    //cout << "doTry " << thisInstance << endl;

    try
    {
        IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
        IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
        IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);

        // Result is discared, nil or exception returned instead.
        /*IoObject* result = */ IoMessage_locals_performOn_(runMessage, runLocals, runTarget);
    }
    catch (ScriptException const& ex)
    {
        //cout << "exitTry " << thisInstance << " returning script error " << ex.what() << endl;
        return ex.getSelf();
    }
    // Don't catch all exceptions with ... below.  There could be a higher C++ frame
    // which recognizes the exception type, so we don't want to just eat it here.
    // catch (...)
    //{
        //cout << "Caught unspecified exception" << endl;
        //cout << "exitTry " << thisInstance << " returning unspecified error" << endl;
        //throw; // rethrow for higher C++ frame to handle.
    //}

    //cout << "exitTry " << thisInstance << endl;

    // discard result, return nil on success, catch and return exception on error.
    return IONIL(self);
}


extern "C" IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m)
{
    ScriptException se(self);
    cout << "throwScriptException: " << se.what() << endl;
    throw se;
}

// replaces IoCoroutine_raiseError
// need iocoroutine for Exception proto slot and to set exception coroutine slot
extern "C" void Iocaste_raiseError(IoObject* self, char* description, IoMessage* m)
{
    // IoState_error does this:
    //IoCoroutine *coroutine = IoState_currentCoroutine(state);
    //IoCoroutine_raiseError(coroutine, description, m);
    //void IoCoroutine_raiseError(IoCoroutine *self, IoSymbol *description, IoMessage *m)
	IoObject *e = IoObject_rawGetSlot_(self, IOSYMBOL("Exception"));

	if (e)
	{
		e = IOCLONE(e);
		IoObject_setSlot_to_(e, IOSYMBOL("error"), IOSYMBOL(description));
		if (m) IoObject_setSlot_to_(e, IOSYMBOL("caughtMessage"), m);
		IoObject_setSlot_to_(e, IOSYMBOL("coroutine"), self);
        throw Iocaste::IoStateError(e, description, m);
	}
}
