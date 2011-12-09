
struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;

namespace Iocaste
{

}

extern "C" IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m);
extern "C" IoObject* raiseException(IoObject *self, IoObject *locals, IoMessage *m);
