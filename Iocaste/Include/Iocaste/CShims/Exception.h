
#include "IoObject.h"


IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IocasteException_proto(void *state);
IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m);
void Iocaste_raiseError(IoObject* self, char* description, IoMessage* m);

