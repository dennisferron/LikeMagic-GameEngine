#include "Exception.hpp"
#include "AbstractOutput.hpp"
using namespace Iocaste::Debugger;

#include <cxxabi.h>
#include <string>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

using namespace std;

AbstractOutput<std::string>* exception_log = nullptr;

void Iocaste::Debugger::setExceptionLog(AbstractOutput<std::string>* log_output_)
{
    exception_log = log_output_;
}

std::string demangle_name(char const* type_name)
{
    int status;
    char* buf = abi::__cxa_demangle(type_name, 0, 0, &status);
    std::string result(buf);
    free(buf);
    return result;
}

void Iocaste::Debugger::logException(std::type_info const& exception_type, std::string msg)
{
    if (exception_log)
    {
        exception_log->WriteData(
            std::string("About to throw exception of type ")
                + demangle_name(exception_type.name())
                    + " message is " + msg
        );
    }
}

ParseException::ParseException(std::string msg_)
    : msg(msg_)
{
}

ParseException::~ParseException() throw()
{
}

char const* ParseException::what() const throw()
{
    return msg.c_str();
}

GeneratorException::GeneratorException(std::string msg_)
    : msg(msg_)
{
}

GeneratorException::~GeneratorException() throw() {}

char const* GeneratorException::what() const throw()
{
    return msg.c_str();
}

TestException::TestException(std::string msg_, std::string expected, std::string actual)
{
    msg = msg_ + " Expected: " + expected + " Actual: " + actual;
}

TestException::~TestException() throw() {}

char const* TestException::what() const throw()
{
    return msg.c_str();
}

LogicError::LogicError(std::string msg_)
    : msg(msg_)
{
}

LogicError::~LogicError() throw() {}

char const* LogicError::what() const throw()
{
    return msg.c_str();
}

BadResponseError::BadResponseError(std::string msg_)
    : msg(msg_)
{
}

BadResponseError::~BadResponseError() throw() {}

char const* BadResponseError::what() const throw()
{
    return msg.c_str();
}
