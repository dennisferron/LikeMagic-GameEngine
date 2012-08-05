
#pragma once

#include "boost/exception/all.hpp"

#include <stdexcept>
#include <string>

namespace Iocaste {
    namespace Debugger {

    class Exception : public virtual boost::exception, public virtual std::exception
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

    class TestException : public virtual Exception
    {
    private:
        std::string msg;

    public:
        TestException(std::string msg, std::string expected, std::string actual);
        ~TestException() throw();
        virtual char const* what() const throw();
    };

    class LogicError : public Exception
    {
    private:
        std::string msg;

    public:
        LogicError(std::string msg_);
        ~LogicError() throw();
        virtual char const* what() const throw();
    };

    }
}
