#include "Exception.hpp"
using namespace Iocaste::Debugger;

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
