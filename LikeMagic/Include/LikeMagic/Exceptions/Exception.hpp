#pragma once

#include "boost/exception/exception.hpp"
#include <stdexcept>
#include <vector>

namespace LM
{
    class Exception : public boost::exception, public std::exception
    {
    private:
        std::string error_msg;
    public:
        virtual char const* what() const throw();
        Exception(std::string error_msg_);
    };
}

