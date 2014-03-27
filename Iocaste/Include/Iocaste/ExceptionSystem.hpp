
struct IoState;
struct IoObject;
typedef IoObject IoMessage;

namespace Iocaste
{

}

IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m);
IoObject* raiseException(IoObject *self, IoObject *locals, IoMessage *m);
