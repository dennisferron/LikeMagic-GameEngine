// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/IoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/ToIoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/FromIoTypeInfo.hpp"
#include "Iocaste/Exception.hpp"
#include "Iocaste/Breakpoint.hpp"
#include "Iocaste/DebugAPI.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"

#include "LikeMagic/SFMO/ExprProxy.hpp"

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

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

// Debugging (to raise breakpoint signal for gdb)
//#include <signal.h>

#include "Iocaste/CShims/IoVMCpp.h"

using namespace std;
using namespace LikeMagic;
using namespace LikeMagic::Marshaling;
using namespace LikeMagic::SFMO;
using namespace Iocaste;
using namespace Iocaste::LikeMagicAdapters;
using namespace LikeMagic::Utility;

// CShims functions
extern "C" {

void iovm_set_pending_breakpoints(IoMessage *self)
{
    IoVM::get(self)->set_pending_breakpoints(self);
}

StepMode_t iovm_hit_breakpoint(void* bp,
    void *self, void *locals, void *m)
{
    Breakpoint& bkpt = *reinterpret_cast<Breakpoint*>(bp);

    return (StepMode_t)io_debugger_break_here(self, locals, m,
        bkpt.breakpoint_number, bkpt.file_name.c_str(),
            bkpt.line_number, bkpt.char_number);
}

StepMode_t iovm_step_stop(
    void *self, void *locals, void *m)
{
    IoMessageData* data = reinterpret_cast<IoMessageData*>(IoObject_dataPointer(m));

    char const* file_name = CSTRING(data->label);
    int line_number = data->lineNumber;
    int char_number = data->charNumber;

    return (StepMode_t)io_debugger_break_here(self, locals, m,
        -1,
        file_name,
        line_number,
        char_number
    );
}

}

IoVM* IoVM::get(IoState* state)
{
    //return reinterpret_cast<IoVM*>(state->callbackContext);
    return static_cast<IoVM*>(state);
}

IoVM* IoVM::get(IoMessage* m)
{
    return get(get_io_state(m));
}

void IoVM::set_pending_breakpoints(IoMessage* m)
{
    IoMessageData* data = reinterpret_cast<IoMessageData*>(IoObject_dataPointer(m));

    data->breakpoint = find_pending_breakpoint(m);

	List_do_(data->args, (ListDoCallback *)iovm_set_pending_breakpoints);

	if (data->next)
	{
		set_pending_breakpoints(data->next);
	}
}

void IoVM::set_breakpoint(int breakpoint_number, const char *file_name, int line_number)
{
    breakpoints.push_back(Breakpoint(breakpoint_number, file_name, line_number, -1));
}

Breakpoint* IoVM::find_pending_breakpoint(std::string file_name, int line_number, int char_number)
{
    for (Breakpoint& bp : breakpoints)
    {
        // TODO:  Some situations may call for just lowest char number
        // TODO:  Use "m" or use separate args?
        if (bp.match(file_name, line_number, char_number))
            return &bp;
    }

    return NULL;
}

Breakpoint* IoVM::find_pending_breakpoint(IoMessage* m)
{
    IoMessageData* data = reinterpret_cast<IoMessageData*>(IoObject_dataPointer(m));
    return find_pending_breakpoint(
        string(CSTRING(data->label)),
        data->lineNumber,
        data->charNumber);
}

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

void print_conv(TypeIndex from, TypeIndex to, AbstractTypeSystem& type_sys)
{
    type_sys.print_conv_chain(from, to);
}

template <typename From>
void print_conv(TypeIndex to, AbstractTypeSystem& type_sys)
{
    TypeIndex from = BetterTypeInfo::create_index<From>();
    print_conv(from, to, type_sys);
}

template <typename From, typename To>
void print_conv(AbstractTypeSystem& type_sys)
{
    TypeIndex to = BetterTypeInfo::create_index<To>();
    print_conv<From>(to, type_sys);
}

void IoVM::setShowAllMessages(bool value)
{
    state->showAllMessages = value;
}

IoVM::IoVM(RuntimeTypeSystem& type_sys) : type_system(type_sys), last_exception(0)
{
    state = this;

    // It's very important you static_cast here, if you use
    // reinterpret_cast or allow conversion to void* which
    // is the function arg, you get a different pointer!
    IoState_new_atAddress(static_cast<IoState*>(this));

    IoState_init(state);
    state->callbackContext = reinterpret_cast<void*>(this);

    io_debugger_init(state);

    IoState_exceptionCallback_(state, &io_exception);

    IoObject* bootstrap = IoObject_new(state);

    IoObject_setSlot_to_(state->lobby,
        IoState_symbolWithCString_(state, "bootstrap"),
        bootstrap);

    LM_Proxy = API_io_proto(state);
    IoObject_setSlot_to_(bootstrap, IoState_symbolWithCString_(state, "LikeMagicProxy"),
        LM_Proxy);

    // We want forward to work so that we can suggest method fixes when a method lookup fails.
    IoSymbol* method_symbol = IoState_symbolWithCString_(state, "forward");
    IoObject_addMethod_(LM_Proxy, method_symbol, &API_io_forward);

    LM_Protos = IoObject_new(state);
    IoObject_setSlot_to_(bootstrap, IoState_symbolWithCString_(state, "LM_Protos"),
        LM_Protos);

    add_convs_from_script(type_sys, this);
    add_convs_to_script(type_sys, this);

    LM_CLASS_NO_COPY(type_sys, ITypeSystemObserver)

    // Register this vm
    LM_CLASS_NO_COPY(type_sys, IoVM)
    LM_BASE(IoVM, ITypeSystemObserver)
    LM_FUNC(IoVM, (run_cli)(do_string)(castToIoObjectPointer)(proxy_to_io_obj)(setShowAllMessages))
    LM_FIELD(IoVM, (onRegisterMethod)(onRegisterClass)(onRegisterBase)(onAddProto))

    LM_CLASS_NO_COPY(type_sys, AbstractTypeSystem)
    LM_CLASS_NO_COPY(type_sys, RuntimeTypeSystem)
    LM_BASE(RuntimeTypeSystem, AbstractTypeSystem)

    LM_CLASS(type_sys, IoObject)

    // To convert an Io object to a void*
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Object"), BetterTypeInfo::create_index<void*>(), new LikeMagic::TypeConv::ImplicitConv<IoObject*, void*>);

    // Make general Io objects convertible with IoObject*.
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Object"), BetterTypeInfo::create_index<IoObject*>(), new LikeMagic::TypeConv::NoChangeConv<>);
    type_sys.add_converter_simple(BetterTypeInfo::create_index<IoObject*>(), ToIoTypeInfo::create_index("Object"), new PtrToIoObjectConv);
    type_sys.add_converter_simple(ToIoTypeInfo::create_index("Object"), ToIoTypeInfo::create_index(), new LikeMagic::TypeConv::NoChangeConv<>);

    // Allow LikeMagic proxy objects to be converted to the C/C++ type IoObject*
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("LikeMagic"), BetterTypeInfo::create_index<IoObject*>(), new LikeMagic::TypeConv::NoChangeConv<>);

    LM_CLASS(type_sys, DebugInfo)
    LM_CLASS(type_sys, IoBlock)
    LM_BASE(IoBlock, DebugInfo)

    // Allow conversion of Io blocks to IoObject*
    type_sys.add_converter_simple(FromIoTypeInfo::create_index("Block"), BetterTypeInfo::create_index<IoObject*>(), new LikeMagic::TypeConv::NoChangeConv<>);

    // Allow reference/value conversions for IoBlock.
    type_sys.add_conv<Iocaste::LikeMagicAdapters::IoBlock&, Iocaste::LikeMagicAdapters::IoBlock>();
    type_sys.add_conv<Iocaste::LikeMagicAdapters::IoBlock&, Iocaste::LikeMagicAdapters::IoBlock const&>();

    // You have to have registered the types before you can add protos for them.

    // Make this vm accessible in the bootstrap environment
    add_proto<IoVM&>("io_vm", *this);

    // Also make the abstract type system available by pointer.
    add_proto<RuntimeTypeSystem&>("type_system", type_sys);

    // The object that represents the global namespace.
    //add_proto("namespace", Namespace::global(type_sys).register_functions().create_class_proxy(), false);

    return;
}

void IoVM::register_base(LikeMagic::Marshaling::AbstractClass const* class_, LikeMagic::Marshaling::AbstractClass const* base)
{
    //cout << "Register base " << class_->get_class_name() << " : " << base->get_class_name() << endl << flush;
    //string proto_code = code_to_get_class_proto(class_);
    //do_string(proto_code + " appendProto(" + code_to_get_class_proto(base) + ")");

    if (!onRegisterBase.empty())
        onRegisterBase(class_, base);
}

void IoVM::register_method(LikeMagic::Marshaling::AbstractClass const* class_, std::string method_name, LikeMagic::Marshaling::AbstractCallTargetSelector* method)
{
    //cout << "Register method " << method_name << endl;
    if (!onRegisterMethod.empty())
        onRegisterMethod(class_, method_name, method);
}

void IoVM::register_class(LikeMagic::Marshaling::AbstractClass const* class_)
{
    if (!onRegisterClass.empty())
        onRegisterClass(class_);
        //class_protos[class_->get_type()] = onRegisterClass.eval<IoObject*>(class_);
}

IoVM::~IoVM()
{
    IoState_done(state);

    // Don't free; we're derived from it!
    //IoState_free(state);
}

IoObject* IoVM::castToIoObjectPointer(void* p)
{
    return reinterpret_cast<IoObject*>(p);
}

void IoVM::add_proto(std::string name, AbstractCppObjProxy* proxy, LikeMagic::NamespacePath ns, bool conv_to_script) const
{
    IoObject* clone;
    if (conv_to_script)
    {
        clone = to_script(state->lobby, state->lobby, NULL, proxy);
    }
    else
    {
        IoObject* proto = LM_Proxy;
        clone = API_io_rawClone(proto);
        IoObject_setDataPointer_(clone, proxy);
    }

    //if (onAddProto.empty())
        IoObject_setSlot_to_(LM_Protos, IoState_symbolWithCString_(state, name.c_str()), clone);
    //else
    //    onAddProto(ns, name, clone);
}

IoObject* IoVM::do_string(std::string io_code) const
{
    //std::cout << "IoVM::do_string(" << io_code << ")" << std::endl;
    std::cout << io_code << std::endl;

    IoObject* result = IoState_doCString_(state, io_code.c_str());

    // If we throw the exception here, can't check it in other IoVM code.
    // If we do not throw the exception here, could miss it in user code.
    // TODO:  Use try-catch instead of last_exception check in other IoVM functions.
    //if (last_exception)
    //{
    //    last_exception = 0;
    //    throw std::logic_error("Caught Io exception while running Io code.");
    //}

    return result;
}

void IoVM::run_cli() const
{
    IoState_runCLI(state);
}

ExprPtr IoVM::get_abs_expr(std::string io_code) const
{
    auto io_obj = do_string(io_code);
    static TypeIndex unspec_type = TypeIndex();  // id = -1, type not specified
    return from_script(state->lobby, io_obj, type_system, unspec_type);
}

void IoVM::io_exception(void* context, IoObject* coroutine)
{
    IoCoroutine_rawPrintBackTrace(coroutine);

    IoVM* vm = reinterpret_cast<IoVM*>(context);
	IoObject* e = IoCoroutine_rawException(coroutine);

    cout << "Caught Io exception: ";

    IoObject* self = coroutine;
    IoSymbol* error = IoObject_rawGetSlot_(e, IOSYMBOL("error"));

    cout << CSTRING(error) << endl;

    vm->last_exception = e;
}

void IoVM::mark() const
{
    // If you don't call base mark, child objects don't get marked!
    MarkableObjGraph::mark();

    if (!is_just_testing())
    {
        IoObject_shouldMarkIfNonNull(last_exception);
        IoObject_shouldMarkIfNonNull(LM_Proxy);
    }
}

IoObject* IoVM::proxy_to_io_obj(AbstractCppObjProxy* proxy)
{
    if (!proxy)
        throw logic_error("IoVM::proxy_to_io_obj: proxy argument was NULL.");

    IoObject* proto = LM_Proxy;
    IoObject* clone = API_io_rawClone(proto);
    IoObject_setDataPointer_(clone, proxy);
    return clone;
}

void build_arg_exception(string method_name, TypeInfoList arg_types, int i, int arg_count, std::exception const& e)
{
    throw std::logic_error(
           std::string() + "In call of method " + method_name +
           ", error converting argument " + boost::lexical_cast<std::string>(i) + " of " + boost::lexical_cast<std::string>(arg_count) +
           " to type " + arg_types[i].describe() + " exception was: " + e.what());
}

IoObject* IoVM::perform(IoObject *self, IoObject *locals, IoMessage *m)
{
 	IoVM* iovm = 0;

    if (!IoObject_dataPointer(self))
    {
        return IoObject_perform(self, locals, m);
    }

    try
    {
        if (!IOSTATE->callbackContext)
            throw std::logic_error("The IoState does not have a callbackContext (supposed to contain pointer to IoVM object).");

        iovm = reinterpret_cast<IoVM*>(IOSTATE->callbackContext);

        if (iovm->state != IOSTATE)
            throw std::logic_error("Failed to retrieve IoVM object from IoState callback context.");

        std::string method_name = CSTRING(IoMessage_name(m));
        //std::cout << "perform "  << method_name << std::endl << std::flush;

        //if (method_name == "unsafe_ptr_cast")
        //    cout << "unsafe_ptr_cast used" << endl;

        auto proxy = reinterpret_cast<AbstractCppObjProxy*>(IoObject_dataPointer(self));
        proxy->check_magic();

        auto& type_sys = proxy->get_type_system();

        int arg_count = IoMessage_argCount(m);
        auto* method = proxy->try_get_method(method_name, arg_count);

        // If it's not a C++ method, maybe it is an Io method.  If it is neither,
        // it will end up coming back to us via IoVM::forward where we can throw the method not found exception.
        if (!method)
            return IoObject_perform(self, locals, m);

        std::vector<ExprPtr> args;
        TypeInfoList arg_types = method->get_arg_types();

        for (size_t i=0; i<arg_types.size(); i++)
        {
            try
            {
                ExprPtr expr = get_expr_arg_at(self, locals, m, i, type_sys, arg_types[i]);
                //std::cout << "arg " << i << " expects " << arg_types[i].describe() << " got " << expr->get_type().describe() << std::endl;
                args.push_back(expr);
            }
            catch (ScriptException const&)
            {
                throw;
            }
            catch (std::exception const& e)
            {
                build_arg_exception(method_name, arg_types, i, arg_count, e);
            }
        }

        // Debugging
        //if (method_name == "createHillPlaneMesh")
        //    raise(SIGINT);

        auto result = proxy->call(method, args);
        IoObject* result_obj = iovm->to_script(self, locals, m, result);

        return result_obj;
    }
    catch (Iocaste::Exception& e)
    {
        std::cout << "Caught script exception: " << e.what() << std::endl;
        throw;
    }
    catch (std::logic_error le)
    {
        //std::cout << "Caught exception: " << le.what() << std::endl;
        IoState_error_(IOSTATE,  m, "C++ %s, %s", LikeMagic::Utility::demangle_name(typeid(le).name()).c_str(), le.what());
        return IONIL(self);
    }
    catch (std::exception e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
        IoState_error_(IOSTATE,  m, "C++ %s, %s", LikeMagic::Utility::demangle_name(typeid(e).name()).c_str(), e.what());
        return IONIL(self);
    }
    catch (...)
    {
        cout << "LikeMagic:  Unknown C++ exception, aborting." << endl;
        abort();
    }
}


IoObject* IoVM::forward(IoObject *self, IoObject *locals, IoMessage *m)
{
    std::string method_name = CSTRING(IoMessage_name(m));
    int arg_count = IoMessage_argCount(m);

    //std::string error_msg = "No C++ object on IoVM::forward " + method_name;
    //IOASSERT(IoObject_dataPointer(self), error_msg.c_str());

    // This causes infinite recursion, so just assert instead
    //if (!IoObject_dataPointer(self))
        //return IoObject_forward(self, locals, m);

    if (!IoObject_dataPointer(self))
    {
        string msg = "Lookup failed for method " + method_name + " with " + boost::lexical_cast<string>(arg_count) + " arguments and the object does not have a LikeMagic C++ Proxy attached.";
        IOASSERT(IoObject_dataPointer(self), msg.c_str());
        return IONIL(self);
    }

    try
    {
        std::cout << "forward "  << method_name << std::endl;

        auto proxy = reinterpret_cast<AbstractCppObjProxy*>(IoObject_dataPointer(self));
        proxy->check_magic();

        proxy->suggest_method(method_name, arg_count);

        // Never get here; suggest_method always throws.
        return IONIL(self);
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
    catch (...)
    {
        cout << "LikeMagic:  Unknown C++ exception, aborting." << endl;
        abort();
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
    else if (has_conv)
    {
        ExprPtr to_expr = type_sys.try_conv(from_expr, to_io_type);
        boost::intrusive_ptr<AbstractToIoObjectExpr> io_expr = static_cast<AbstractToIoObjectExpr*>(to_expr.get());
        IoObject* io_obj = io_expr->eval_in_context(self, locals, m);
        delete proxy;
        return io_obj;
    }
    else
    {
        IoObject* proto;

        proto = LM_Proxy;
        /*
        TypeIndex type = proxy->get_type().class_type();
        auto iter = class_protos.find(type);
        if (iter != class_protos.end())
        {
            proto = iter->second;
        }
        else
        {
            cout << "Warning: no class proto registered for type " << type.describe() << endl;
            proto = LM_Proxy;
        }
        */

        IoObject* clone = IOCLONE(proto);
        IoObject_setDataPointer_(clone, proxy);

        return clone;
    }
}


