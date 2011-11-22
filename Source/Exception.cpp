
#include "Iocaste/Exception.hpp"

#include "Iocaste/CShims/Exception.h"
#include "IoState.h"

#include "IoObject.h"

#include <iostream>
using namespace std;

// TODO:  move doTry to Object try
extern "C" IoObject *IocasteException_proto(void *state)
{
    cout << "IocasteException_proto" << endl;

	IoObject *self = IoObject_new(state);
	IoTag *tag = IoTag_newWithName_("Exception");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoObject_rawClone);
	IoObject_tag_(self, tag);

	IoState_registerProtoWithFunc_((IoState*)state, self, IocasteException_proto);

	{
		IoMethodTable methodTable[] = {
			{"doTry", doTry},
			{NULL, NULL}
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}

// TODO:  move this to Object try
extern "C" IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m)
{
    cout << "doTry" << endl;

    IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
	IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
	IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);

    IoObject result = IoMessage_locals_performOn_(runMessage, runLocals, runTarget);

    // discard result, return nil on success, catch and return exception on error.
    return IONIL(self);
}
