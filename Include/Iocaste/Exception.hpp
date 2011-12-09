
#include "boost/exception/exception.hpp"
#include <stdexcept>

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;

namespace Iocaste
{
    class Exception : boost::exception, std::exception
    {
    };

    class ScriptException : Exception
    {
    private:
        IoObject* self;
    public:
        ScriptException(IoObject* self_);
        IoObject* getSelf() const;
    };

    class CppException : Exception
    {
    };
}

extern "C" IoObject* doTry(IoObject *self, IoObject *locals, IoMessage *m);
extern "C" IoObject* throwScriptException(IoObject *self, IoObject *locals, IoMessage *m);
