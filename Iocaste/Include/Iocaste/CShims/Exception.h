
#include "IoObject.h"

#ifdef __cplusplus
extern "C" {
#endif

IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IocasteException_proto(void *state);
IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m);
void Iocaste_raiseError(IoObject* self, char* description, IoMessage* m);

#ifdef __cplusplus
}
#endif
