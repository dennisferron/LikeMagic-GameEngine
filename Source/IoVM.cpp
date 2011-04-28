// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/IoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/ToIoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/FromIoTypeInfo.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"

#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#include "boost/lexical_cast.hpp"

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

extern "C"
{
    void collector_free(void* ptr)
    {
        IoObject* io_obj = reinterpret_cast<IoObject*>(ptr);
        IoState* state = IoObject_state(io_obj);
        IoVM* iovm = reinterpret_cast<IoVM*>(state->callbackContext);
        iovm->on_collector_free(io_obj);
    }
}

/*
struct SequenceToToIoTypeInfoConv : public LikeMagic::TypeConv::AbstractTypeConverter
{
    AbstractTypeSystem const& type_sys;
    SequenceToToIoTypeInfoConv(AbstractTypeSystem const& type_sys_) : type_sys(type_sys_) {}

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        auto str_expr = type_sys.try_conv<std::string>(expr);
        return Term<ToIoTypeInfo, true>::create(str_expr->eval());
    }

    virtual std::string describe() const { return "SequenceToToIoTypeInfoConv"; }
};
*/

// The difference between this and a no-change or implicit conv is this evals in context to return IoObject* directly.
struct PtrToIoObjectConv : public LikeMagic::TypeConv::AbstractTypeConverter
{
    static IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m, IoObject* value)
    {
        return value;
    }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return ToIoObjectExpr<IoObject*, PtrToIoObjectConv>::create(expr);
    }

    virtual std::string describe() const { return "PtrToIoObjectConv"; }
};


IoVM::IoVM(RuntimeTypeSystem& type_sys) : type_system(type_sys),
    record_freed_flag(false), free_watch_flag(false)
{
    // IoObjectExpr expression holds unconverted Io objects; it has type of struct IoObjectExprTag.
    //type_sys.add_type(BetterTypeInfo::create_index<IoObjectExprTag>());

    add_convs_from_script(type_sys, this);
    add_convs_to_script(type_sys, this);

    // Register this vm
    LM_CLASS_NO_COPY(type_sys, IoVM)
    LM_FUNC(IoVM, (run_cli)(do_string)(castToIoObjectPointer)(record_freed_objects)(set_record_freed_objects)
            (watch_freed_objects)(set_watch_freed_objects)(add_watch_for_freed_object)(check_if_freed))

    /*
    LM_CLASS(runtime_type_sys, AbstractTypeInfo)

    LM_CLASS(runtime_type_sys, ToIoTypeInfo)
    LM_BASE(ToIoTypeInfo, AbstractTypeInfo)
    LM_CONSTR(ToIoTypeInfo,,)
    LM_CONSTR(ToIoTypeInfo,, std::string)


    // Make the ToIoTypeInfo constructible from a string so that
    // the proxy as_script_type() can be called using a string and receive a ToIoTypeInfo.
    // Using Sequence instead of string for the from type so as not to conflict with other languages' type conversions.
    //type_sys.add_converter_simple(FromIoTypeInfo::create_index("Sequence"), BetterTypeInfo::create_index<ToIoTypeInfo>(), new SequenceToToIoTypeInfoConv(type_sys));


    LM_CLASS(runtime_type_sys, FromIoTypeInfo)
    LM_BASE(FromIoTypeInfo, AbstractTypeInfo)
    LM_CONSTR(FromIoTypeInfo,, std::string)

    */

    LM_CLASS_NO_COPY(type_sys, AbstractTypeSystem)
    LM_CLASS_NO_COPY(type_sys, RuntimeTypeSystem)
    LM_BASE(RuntimeTypeSystem, AbstractTypeSystem)

    LM_CLASS(type_sys, IoObject)

    // To convert an Io object to a void*
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Object"), BetterTypeInfo::create_index<void*>(), new LikeMagic::TypeConv::ImplicitConv<IoObject*, void*>);

    // Make general Io objects convertible with IoObject*.
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Object"), BetterTypeInfo::create_index<IoObject*>(), new LikeMagic::TypeConv::NoChangeConv);
    type_sys.add_converter_simple(BetterTypeInfo::create_index<IoObject*>(), ToIoTypeInfo::create_index("Object"), new PtrToIoObjectConv);
    type_sys.add_converter_simple(ToIoTypeInfo::create_index("Object"), ToIoTypeInfo::create_index(), new LikeMagic::TypeConv::NoChangeConv);

    // Allow conversion of Io blocks to IoObject*
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Block"), BetterTypeInfo::create_index<IoObject*>(), new LikeMagic::TypeConv::NoChangeConv);

    // Allow reference/value conversions for IoBlock.
    type_sys.add_conv<LikeMagic::Backends::Io::IoBlock&, LikeMagic::Backends::Io::IoBlock>();
    type_sys.add_conv<LikeMagic::Backends::Io::IoBlock&, LikeMagic::Backends::Io::IoBlock const&>();

    self = IoState_new();
    IoState_init(self);
    self->callbackContext = reinterpret_cast<void*>(this);
    original_free_func = self->collector->freeFunc;
    Collector_setFreeFunc_(self->collector, &collector_free);

    IoObject_setSlot_to_(self->lobby, SIOSYMBOL("LikeMagic"),
        API_io_proto(self));

    string io_code = "LikeMagic classes := Object clone do(type=\"C++Classes\")";
    IoObject* classes = do_string(io_code);

    if (!classes)
    {
        throw std::logic_error("Cannot create LikeMagic classes object.");
    }

    type_system.add_type_system_observer(this);

    // You have to have registered the types before you can add protos for them.

    // Add a proto to support all the static class members and namespace level C++ functions.
    add_proto<StaticMethod>("CppFunc");

    // Make this vm itself accessible
    add_proto<IoVM&>("IoVM", *this);

    // Also make the abstract type system available by pointer.
    add_proto<RuntimeTypeSystem&>("CppTypeSystem", type_sys);
}

void IoVM::register_base(LikeMagic::Marshaling::AbstractClass* class_, LikeMagic::Marshaling::AbstractClass const* base)
{
    //cout << "Register base " << class_->get_class_name() << " : " << base->get_class_name() << endl << flush;
    do_string("LikeMagic classes " + class_->get_class_name() + " appendProto(LikeMagic classes " + base->get_class_name() + ")");
}

void IoVM::register_method(LikeMagic::Marshaling::AbstractClass* class_, std::string method_name, LikeMagic::Marshaling::AbstractCallTargetSelector* method)
{
    //cout << "Register method " << class_->get_class_name() << "::" << method_name << endl << flush;
    std::string class_name = class_->get_class_name();
    std::string code = "LikeMagic classes " + class_name;
    IoObject* mset_proto = do_string(code);
    vector<string> method_names;
    method_names.push_back(method_name);
    auto mtbl = make_io_method_table(method_names);
    IoObject_addMethodTable_(mset_proto, mtbl);
    delete[] mtbl;
}


void IoVM::register_class(TypeIndex type_index, LikeMagic::Marshaling::AbstractClass* class_)
{
    //cout << "Register class " << class_->get_class_name() << endl << flush;

    string io_code = "LikeMagic classes";
    IoObject* classes = do_string(io_code);

    if (!classes)
    {
        throw std::logic_error("Cannot get LikeMagic classes object.");
    }

    std::string name = class_->get_class_name();
    do_string("LikeMagic classes " + name + " := LikeMagic clone do(type = \"" + name + "\")");

    std::string code = "LikeMagic classes " + name;
    IoObject* mset_proto = do_string(code);

    cpp_protos[type_index] = mset_proto;

    if (!mset_proto)
    {
        throw std::logic_error("Error getting proto for methodset, return value null:  " + code);
    }

    auto mtbl = make_io_method_table(type_system.get_method_names(type_index));
    IoObject_addMethodTable_(mset_proto, mtbl);
    delete[] mtbl;

    // Give the proto a C++ proxy object so constructors and proxy methods can be called on it.
    AbstractCppObjProxy* proxy = type_system.create_class_proxy(type_index);
    IoObject_setDataPointer_(mset_proto, proxy);

    // Then hook up all the bases as protos
    auto base_names = class_->get_base_names();
    for (auto base=base_names.begin(); base != base_names.end(); base++)
        do_string("LikeMagic classes " + class_->get_class_name() + " appendProto(LikeMagic classes " + *base + ")");
}

IoVM::~IoVM()
{
    IoState_free(self);
}

IoObject* IoVM::castToIoObjectPointer(void* p)
{
    return reinterpret_cast<IoObject*>(p);
}

void IoVM::add_proto(std::string name, AbstractCppObjProxy* proxy, bool conv_to_script) const
{
    IoObject* clone;
    if (conv_to_script)
    {
        clone = to_script(self->lobby, self->lobby, NULL, proxy);
    }
    else
    {
        string io_code = "LikeMagic classes " + proxy->get_class_name() + " clone";
        clone = do_string(io_code);
        IoObject_setDataPointer_(clone, proxy);
    }

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

ExprPtr IoVM::get_abs_expr(std::string io_code) const
{
    auto io_obj = do_string(io_code);
    return from_script(self->lobby, io_obj, type_system);
}


IoObject* IoVM::io_userfunc(IoObject *self, IoObject *locals, IoMessage *m)
{
    IOASSERT(IoObject_dataPointer(self), "No C++ object");
    try
    {
        std::string method_name = CSTRING(IoMessage_name(m));

        //std::cout << "Method called is: "  << method_name << std::endl;

        auto proxy = reinterpret_cast<AbstractCppObjProxy*>(IoObject_dataPointer(self));
        proxy->check_magic();

        auto& type_sys = proxy->get_type_system();

        int arg_count = IoMessage_argCount(m);
        auto* method = proxy->get_method(method_name, arg_count);

        std::vector<ExprPtr> args;
        TypeInfoList arg_types = method->get_arg_types();

        for (size_t i=0; i<arg_types.size(); i++)
        {
            try
            {
                ExprPtr expr = get_expr_arg_at(self, locals, m, i, type_sys);
                //std::cout << "arg " << i << " expects " << arg_types[i].describe() << " got " << expr->get_type().describe() << std::endl;
                args.push_back(expr);
            }
            catch (std::logic_error le)
            {
                throw std::logic_error(std::string() + "Error converting argument " + boost::lexical_cast<std::string>(i) + ": " + le.what());
            }
            catch (std::exception e)
            {
                throw std::logic_error(std::string() + "Error converting argument " + boost::lexical_cast<std::string>(i) + ": " + e.what());
            }
        }

        if (!IOSTATE->callbackContext)
            throw std::logic_error("The IoState does not have a callbackContext (supposed to contain pointer to IoVM object).");

        IoVM* iovm = reinterpret_cast<IoVM*>(IOSTATE->callbackContext);

        if (iovm->self != IOSTATE)
            throw std::logic_error("Failed to retrieve IoVM object from IoState callback context.");

        auto result = proxy->call(method, args);
        return iovm->to_script(self, locals, m, result);
    }
    catch (std::logic_error le)
    {
        //std::cout << "Caught exception: " << le.what() << std::endl;
        IoState_error_(IOSTATE,  m, "C++ %s, %s", LikeMagic::Utility::demangle_name(typeid(le).name()).c_str(), le.what());
        return IONIL(self);
    }
    catch (std::exception e)
    {
        //std::cout << "Caught exception: " << e.what() << std::endl;
        IoState_error_(IOSTATE,  m, "C++ %s, %s", LikeMagic::Utility::demangle_name(typeid(e).name()).c_str(), e.what());
        return IONIL(self);
    }
}


IoObject* IoVM::to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy) const
{
    static TypeIndex to_io_type = ToIoTypeInfo::create_index();

    if (!proxy)
        return IOSTATE->ioNil;
    else
        proxy->check_magic();

    AbstractTypeSystem const& type_sys = proxy->get_type_system();
    ExprPtr from_expr = proxy->get_expr();

    bool is_terminal = proxy->is_terminal();
    bool disable_to_script = proxy->disable_to_script_conv();
    bool has_conv = is_terminal && !disable_to_script && type_sys.has_conv(from_expr->get_type(), to_io_type);

    if (!disable_to_script && proxy->get_expr()->is_null())
    {
        return IOSTATE->ioNil;
    }
    if (has_conv)
    {
        ExprPtr to_expr = type_sys.try_conv(from_expr, to_io_type);
        boost::intrusive_ptr<AbstractToIoObjectExpr> io_expr = static_cast<AbstractToIoObjectExpr*>(to_expr.get());
        IoObject* io_obj = io_expr->eval_in_context(self, locals, m);
        delete proxy;
        return io_obj;
    }
    else
    {
        auto iter = cpp_protos.find(proxy->get_type().class_type());

        if (iter == cpp_protos.end())
            throw std::logic_error("No class proto for " + proxy->get_type().describe() );

        IoObject* proto = iter->second;
        IoObject* clone = IOCLONE(proto);
        IoObject_setDataPointer_(clone, proxy);

        return clone;
    }
}

void IoVM::on_collector_free(IoObject* io_obj)
{
    if(record_freed_flag)
       freed_objects.insert(io_obj);

    if(free_watch_flag && watch_for_free.find(io_obj) != watch_for_free.end())
        throw std::runtime_error("Watch object freed: " + watch_for_free[io_obj]);

    // BAD THINGS happen if you don't allow the original free function run.
    // I imagine it must be doing some necessary cleanup or fixing up collector marker pointers.
    (*original_free_func)(io_obj);
}

bool IoVM::record_freed_objects() const
{
    return record_freed_flag;
}

void IoVM::set_record_freed_objects(bool value)
{
    record_freed_flag = value;
}

bool IoVM::watch_freed_objects() const
{
    return free_watch_flag;
}

void IoVM::set_watch_freed_objects(bool value)
{
    free_watch_flag = value;
}

void IoVM::add_watch_for_freed_object(IoObject* io_obj, std::string message)
{
    watch_for_free[io_obj] = message;
}

bool IoVM::check_if_freed(IoObject* io_obj)
{
    return freed_objects.find(io_obj) != freed_objects.end();
}





