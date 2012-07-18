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
