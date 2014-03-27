
#include "Iocaste/Exception.hpp"

#include "Iocaste/CShims/Exception.h"
#include "IoState.h"
#include "IoNumber.h"

#include "IoObject.h"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

char const* Iocaste::Exception::protoId = "IocasteException";

intptr_t Stack_pushMarkPoint(Stack *self);
int Stack_popMarkPoint_(Stack *self, intptr_t mark);

#include <iostream>
using namespace std;

using namespace Iocaste;

char const* Iocaste::Exception::what() const throw()
{
    return "Iocaste::Exception";
}


ScriptException::ScriptException(IoObject* self_)
    : self(self_), errorText(getErrorText(self_)), backTraceString(getBackTraceString(self)), lineNumber(getLineNumber(self))
{
    cout << "ScriptException constructed "
        << " errorText = " << errorText
        << " lineNumber = " << lineNumber << endl
        << " backtrace = " << backTraceString << endl;
}

ScriptException::~ScriptException() throw()
{
}


IoObject* ScriptException::getSelf() const
{
    return self;
}

char const* ScriptException::what() const throw()
{
    return (errorText+"\n"+backTraceString+"\nAt line number "+boost::lexical_cast<std::string>(lineNumber)).c_str();
}

int ScriptException::getLineNumber() const
{
    return lineNumber;
}

std::string ScriptException::getErrorText() const
{
    return errorText;
}

std::string ScriptException::getBackTraceString() const
{
    return backTraceString;
}

std::string ScriptException::getErrorText(IoObject* self)
{
    if (!self)
        return "<<Missing Io Exception object>>";

    // This freezes up if the exception causes destruction of the IoVM object
    // that's why we cache the what() message in a string in the exception constructor.
	IoObject *msg = IoObject_rawGetSlot_(self, IOSYMBOL("error"));

	if (!msg)
        return "<<Io Exception object has no 'error' slot>>";

	if (!ISSEQ(msg))
        return "<<Io Exception 'error' slot is not a string>>";

    return CSTRING(msg);
}

std::string ScriptException::getBackTraceString(IoObject* self)
{
    if (self == nullptr)
        return "no backtrace - Io object is null";

    IoObject* coro = IoState_on_doCString_withLabel_(IOSTATE, self, "coroutine", "[Exception.cpp]");
	IoObject *backt = coro? IoObject_rawGetSlot_(coro, IOSYMBOL("backTraceString")) : NULL;

	if (!backt)
	{
	    return "Error getting backtrace.";
	}
	else
	{
        IoObject* msg = IoState_on_doCString_withLabel_(IOSTATE, self, "coroutine backTraceString", "[Exception.cpp]");

        if (!msg)
            return "<<Failed to get back trace string>>";

        if (!ISSEQ(msg))
            return "<<Back trace 'string' is not a string>>";

        return CSTRING(msg);
	}
}

int ScriptException::getLineNumber(IoObject* self)
{
    if (self == nullptr)
        return 0;

    IoObject* message = IoObject_getSlot_(self, IOSYMBOL("caughtMessage"));
    IoObject* lineNumberObj = IoObject_getSlot_(self, IOSYMBOL("lineNumber"));
    int lineNumber = IoNumber_asInt(lineNumberObj);
    return lineNumber;
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


IoObject *IocasteException_proto(void *state)
{
	IoObject *self = IoObject_new(state);
	IoTag *tag = IoTag_newWithName_("Exception");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoObject_rawClone);
	IoObject_tag_(self, tag);

	IoState_registerProtoWithId_((IoState *)state, self, Iocaste::Exception::protoId);

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

IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m)
{
    size_t mark = 0;

    try
    {
        // Should marking the stack go before or after getting the runTarget, runLocals, runMessage?
        // Calling valueArgAt can do performOn, don't know if the stack state is significant.  I am
        // thinking it is safest to mark the stack first so it all gets reversed on a caught exception.
        mark = IOSTATE->currentIoStack->push_mark(MarkReason::TryBlock);

        IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
        IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
        IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);
        IoMessage_locals_performOn_(runMessage, runLocals, runTarget);

        if (mark)
            IOSTATE->currentIoStack->pop_to_mark_point(mark);
    }
    catch (ScriptException const& ex)
    {
        if (mark)
            IOSTATE->currentIoStack->pop_to_mark_point(mark);
        return ex.getSelf();
    }
    catch (...)
    {
        if (mark)
            IOSTATE->currentIoStack->pop_to_mark_point(mark);
        throw;
    }

    return IONIL(self);
}

IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m)
{
    ScriptException se(self);
    //cout << "throwScriptException: " << se.what() << endl;
    throw se;
}

// replaces IoCoroutine_raiseError
// need iocoroutine for Exception proto slot and to set exception coroutine slot
void Iocaste_raiseError(IoObject* self, char* description, IoMessage* m)
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
