#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"

#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace LikeMagic::Marshaling;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Backends::Io;
using namespace LikeMagic::Utility;


IoVM::IoVM(AbstractTypeSystem& type_system_) : type_system(type_system_)
{

    // Register this vm
    LM_CLASS(dynamic_cast<RuntimeTypeSystem&>(type_system_), IoVM)
    LM_FUNC(IoVM, (run_cli)(do_string))

    type_system_.add_conv<LikeMagic::Backends::Io::IoBlock&, LikeMagic::Backends::Io::IoBlock>();
    type_system_.add_conv<LikeMagic::Backends::Io::IoBlock&, LikeMagic::Backends::Io::IoBlock const&>();

    self = IoState_new();
    IoState_init(self);

    IoObject_setSlot_to_(self->lobby, SIOSYMBOL("LikeMagic"),
        API_io_proto(self));

    string io_code = "LikeMagic classes := Object clone do(type=\"C++Classes\")";
    IoObject* classes = do_string(io_code);

    if (!classes)
    {
        throw std::logic_error("Cannot get LikeMagic classes object.");
    }

    // Get the methods of all the classes
    auto types = type_system.get_registered_types();
    for (auto it=types.begin(); it != types.end(); it++)
    {
        std::string name = type_system.get_class_name(*it);
        do_string("LikeMagic classes " + name + " := LikeMagic clone do(type = \"" + name + "\")");

        std::string code = "LikeMagic classes " + name;
        IoObject* mset_proto = do_string(code);

        if (!mset_proto)
        {
            throw std::logic_error("Error getting proto for methodset, return value null:  " + code);
        }

        IoObject_addMethodTable_(mset_proto,
                make_io_method_table(type_system.get_method_names(*it)));

        // Give the proto a C++ proxy object so constructors and proxy methods can be called on it.
        AbstractCppObjProxy* proxy = type_system.create_class_proxy(*it);
        IoObject_setDataPointer_(mset_proto, proxy);
    }

    // Then hook up all the bases as protos
    for (auto it=types.begin(); it != types.end(); it++)
    {
        auto base_names = type_system.get_base_names(*it);
        for (auto base=base_names.begin(); base != base_names.end(); base++)
            do_string("LikeMagic classes " + type_system.get_class_name(*it) + " appendProto(LikeMagic classes " + *base + ")");
    }

    // You cannot add protos until after all the above code is finished.

    // Add a proto to support all the static class members and namespace level C++ functions.
    add_proto<StaticMethod>("CppFunc");

    // Make this vm itself accessible
    add_proto<IoVM&>("IoVM", *this);

    // Also make the abstract type system available by pointer.
    add_proto<AbstractTypeSystem&>("CppTypeSystem", type_system_);
}

IoVM::~IoVM()
{
    IoState_free(self);
}

void IoVM::add_proto(std::string name, AbstractCppObjProxy* proxy) const
{
    string io_code = "LikeMagic classes " + proxy->get_class_name() + " clone";
    IoObject* clone = do_string(io_code);
    IoObject_setDataPointer_(clone, proxy);
    IoObject_setSlot_to_(self->lobby, SIOSYMBOL(name.c_str()), clone);
}

IoObject* IoVM::do_string(std::string io_code) const
{
    //std::cout << "IoVM::do_string(" << io_code << ")" << std::endl;

    IoObject* result = IoState_doCString_(self, io_code.c_str());

    if (!result)
        throw std::logic_error("IoVM::do_string: IoState_doCString_ returned null when executing code this Io code: " + io_code);

    return result;
}

void IoVM::run_cli() const
{
    IoState_runCLI(self);
}

boost::intrusive_ptr<AbstractExpression> IoVM::get_abs_expr(std::string io_code, BetterTypeInfo type) const
{
    auto io_obj = do_string(io_code);
    return from_script(self->lobby, io_obj, type, type_system);
}
