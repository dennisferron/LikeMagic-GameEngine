
#include "boost/exception/exception.hpp"
#include <stdexcept>

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;

namespace Iocaste
{
    class Exception : public boost::exception, public std::exception
    {
    };

    class ScriptException : public Exception
    {
    private:
        IoObject* self;
    public:
        ScriptException(IoObject* self_);
        IoObject* getSelf() const;
        virtual char const* what() const throw();
    };

    class CppException : public Exception
    {
    };

    // TODO:  This is blanket exception to replace IoState_error; Parsing should throw a ParseError instead.
    class IoStateError : public ScriptException
    {
    private:
        std::string description;
        IoObject* message;
    public:
        IoStateError(IoObject* self, std::string description_, IoObject* message_);
        virtual ~IoStateError() throw();
        IoObject* getMessage() const;
        virtual char const* what() const throw();
    };
}

