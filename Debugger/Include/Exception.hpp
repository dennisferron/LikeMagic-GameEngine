
#pragma once

#include "boost/exception/exception.hpp"
#include <stdexcept>
#include <string>

namespace Iocaste {
    namespace Debugger {

    class Exception : public boost::exception, public std::exception
    {
    public:
        virtual char const* what() const throw() = 0;
    };

    class ParseException : public Exception
    {
    private:
        std::string msg;

    public:
        ParseException(std::string msg_);
        ~ParseException() throw();
        virtual char const* what() const throw();
    };

    class GeneratorException : public Exception
    {
    private:
        std::string msg;

    public:
        GeneratorException(std::string msg_);
        ~GeneratorException() throw();
        virtual char const* what() const throw();
    };

    class TestException : public Exception
    {
    private:
        std::string msg;

    public:
        TestException(std::string msg, std::string expected, std::string actual);
        ~TestException() throw();
        virtual char const* what() const throw();
    };

    }
}
