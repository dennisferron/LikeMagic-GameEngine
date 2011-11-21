
#include "Iocaste/Exception.hpp"

#include "Iocaste/CShims/Exception.h"
#include "IoState.h"


extern "C" IoObject *IocasteException_proto(void *state)
{
	IoObject *self = IoObject_new(state);
	IoTag *tag = IoTag_newWithName_("Exception");
	IoTag_state_(tag, state);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoObject_rawClone);
	IoObject_tag_(self, tag);

	IoState_registerProtoWithFunc_(state, self, IocasteException_proto);

	{
		IoMethodTable methodTable[] = {
			{"doTry", doTry},
			{NULL, NULL}
		};
		IoObject_addMethodTable_(self, methodTable);
	}
	return self;
}


extern "C" IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m)
{
    IoObject *runTarget  = IoMessage_locals_valueArgAt_(m, locals, 2);
	IoObject *runLocals  = IoMessage_locals_valueArgAt_(m, locals, 1);
	IoObject *runMessage = IoMessage_locals_valueArgAt_(m, locals, 0);

    return IoMessage_locals_performOn_(runMessage, runLocals, runTarget);
}
