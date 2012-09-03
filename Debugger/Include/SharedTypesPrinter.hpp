#include "SharedTypes.hpp"
#include "boost/variant/static_visitor.hpp"

#include <iostream>
#include <vector>

namespace Iocaste { namespace Debugger {

struct SharedTypesPrinter : boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& t) const
    {
        static_assert(sizeof(T) && false, "No debug printer defined for type T");
    }

    void operator()(const int& t) const
    {
        std::cerr << "int " << t;
    }

    void operator()(SharedTypes::GdbResponseFunctionArg const& t) const
    {
        std::cerr << "Arg: " << t.name << t.equals;
        (*this)(t.value);
    }

    void operator ()(const SharedTypes::AddressIn& t) const
    {
        std::cerr << "AddressIn: ";
        (*this)(t.address);
    }

    void operator ()(const SharedTypes::FromModule& t) const
    {
        std::cerr << "FromModule: " << t.module_name;
    }

    void operator ()(const SharedTypes::AtFile& t) const
    {
        std::cerr << "AtFile: " << t.file_name;
    }

    void operator ()(const SharedTypes::VariableEquals& t) const
    {
        std::cerr << "variable equals " << t.name << t.equals;

        if (t.type_cast)
            (*this)(*t.type_cast);
        else
            std::cerr << "(no type cast) ";

        (*this)(t.value);
    }

    void operator ()(const SharedTypes::NoLocals& t) const
    {
        std::cerr << "no locals: " << t.text;
    }

    void operator ()(const SharedTypes::GdbStruct& t) const
    {
        std::cerr << "gdb struct {" << t.contents << "}";
    }

    void operator ()(const std::string& t) const
    {
        std::cerr << "std::string " << t;
    }

    void operator ()(const SharedTypes::TypeCast& t) const
    {
        std::cerr << "type_cast " << t.value;
    }

    void operator ()(const SharedTypes::GdbValue& t) const
    {
        std::cerr << "GdbValue ";
        boost::apply_visitor(*this, t.value);
        if (t.value_as_string)
            std::cerr << " \"" << t.value_as_string->text << "\"";
    }

    void operator ()(const SharedTypes::GdbAddress& t) const
    {
        std::cerr << "GdbAddress " << t.hex_value;
    }

    void operator()(std::vector<SharedTypes::GdbValue> const& t) const
    {
        std::cerr << "vector<GdbValue> size " << t.size() << ": ";
        for (auto arg : t)
        {
            (*this)(arg);
            std::cerr << ", ";
        }
    }

    void operator()(std::vector<SharedTypes::GdbResponseFunctionArg> const& t) const
    {
        std::cerr << "vector<Args> size " << t.size() << ": ";
        for (auto arg : t)
        {
            (*this)(arg);
            std::cerr << ", ";
        }
    }

};


}}
