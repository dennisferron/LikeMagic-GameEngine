
#pragma once

#include "boost/exception/all.hpp"

#include <stdexcept>
#include <string>
#include <typeinfo>

namespace Iocaste { namespace Debugger {

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

class BadResponseError : public Exception
{
private:
    std::string msg;

public:
    BadResponseError(std::string msg_);
    ~BadResponseError() throw();
    virtual char const* what() const throw();
};

template <typename T> class AbstractOutput;
void setExceptionLog(AbstractOutput<std::string>* log_output_);
void logException(std::type_info const& exception_type, std::string msg);

template <typename T>
void raiseError(T const& e)
{
    logException(typeid(T), e.what());
    throw boost::enable_current_exception(e);
}

template <typename T>
void logError(T const& e)
{
    logException(typeid(T), e.what());
}

}}
