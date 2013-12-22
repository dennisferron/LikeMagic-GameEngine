#include "LikeMagic/Exceptions/Exception.hpp"

using namespace LM;

char const* Exception::what() const throw()
{
    return error_msg.c_str();
}

Exception::Exception(std::string error_msg_)
    : error_msg(error_msg_)
{
}
