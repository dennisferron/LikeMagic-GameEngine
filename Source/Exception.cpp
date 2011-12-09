
#include "Iocaste/Exception.hpp"

#include "Iocaste/CShims/Exception.h"
#include "IoState.h"

#include "IoObject.h"

#include <iostream>
using namespace std;

using namespace Iocaste;

ScriptException::ScriptException(IoObject* self_) : self(self_) {}

IoObject* ScriptException::getSelf() const
{
    return self;
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
    cout << "doTry" << endl;

    try
    {
        IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
        IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
        IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);

        // Result is discared, nil or exception returned instead.
        /*IoObject* result = */ IoMessage_locals_performOn_(runMessage, runLocals, runTarget);
    }
    catch (ScriptException& ex)
    {
        return ex.getSelf();
    }
    catch (...)
    {
        cout << "Caught unspecified exception" << endl;
        // TODO:  Create an IoError object and return it.
        return IONIL(self);
    }


    // discard result, return nil on success, catch and return exception on error.
    return IONIL(self);
}


extern "C" IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m)
{
    cout << "throwException" << endl;
    throw ScriptException(self);
}


