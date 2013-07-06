
#include "LikeMagic/Interprocess/SharedArgTransporter.hpp"
#include "LikeMagic/Interprocess/MarshalByCopyConstructor.hpp"

using namespace LikeMagic::Interprocess;

SharedArgTransporter::SharedArgTransporter(AbstractTypeSystem& type_system_)
{
    add_marshaller_by_type<MarshalByCopyConstructor, int>(type_system_);
    add_marshaller_by_type<MarshalByCopyConstructor, float>(type_system_);
}

AbstractSharedArgMarshaller& SharedArgTransporter::get_marshaller(TypeIndex arg_type) const
{
    auto iter = how_marshal.find(arg_type);
    if (iter != how_marshal.end())
    {
        return *(iter->second);
    }
    else
    {
        throw std::logic_error("No marshaller for type x");
    }
}

void SharedArgTransporter::add_marshaller(TypeIndex type, ArgMarshaller marshaller)
{
    how_marshal[type] = marshaller;
}

void SharedArgTransporter::write_args(TypeInfoList arg_types, void* buffer, ArgList args)
{
    if (arg_types.size() != args.size())
        throw std::logic_error("Number of args passed does not match number of args of the method.");

    char* location = (char*)buffer;
    for (size_t i=0; i<args.size(); ++i)
    {
        ExprPtr arg = args[i];
        TypeIndex arg_type = arg_types[i];
        auto& marshaller = get_marshaller(arg_type);
        marshaller.write(location, arg);
        location += marshaller.size();
    }
}

ArgList SharedArgTransporter::read_args(TypeInfoList arg_types, void* buffer)
{
    ArgList result;
    char* location = (char*)buffer;
    for (TypeIndex arg_type : arg_types)
    {
        auto& marshaller = get_marshaller(arg_type);
        ExprPtr arg_expr = marshaller.read(location);
        result.push_back(arg_expr);
        location += marshaller.size();
    }
    return result;
}



