
#include "LikeMagic/Interprocess/SharedArgTransporter.hpp"
#include "LikeMagic/Interprocess/MarshalByCopyConstructor.hpp"

using namespace LM;

SharedArgTransporter::SharedArgTransporter()
{
    add_marshaller_by_type<MarshalByCopyConstructor, int>();
    add_marshaller_by_type<MarshalByCopyConstructor, float>();
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
    void* location = (char*)buffer;
    for (size_t i=0; i<arg_types.size(); ++i)
    {
        ExprPtr arg = args[i];
        TypeIndex arg_type = arg_types[i];
        location = write_value(arg_type, location, arg);
    }
}

void* SharedArgTransporter::write_value(TypeIndex arg_type, void* location, ExprPtr arg)
{
    auto& marshaller = get_marshaller(arg_type);
    marshaller.write(location, arg);
    return marshaller.size() + (char*)location;
}

std::vector<ExprPtr> SharedArgTransporter::read_args(TypeInfoList arg_types, void* buffer)
{
    std::vector<ExprPtr> arg_list;
    void* location = (char*)buffer;
    for (TypeIndex arg_type : arg_types)
    {
        std::pair<ExprPtr, void*> result = read_value(arg_type, location);
        arg_list.push_back(result.first);
        location = result.second;
    }
    return arg_list;
}

std::pair<ExprPtr, void*> SharedArgTransporter::read_value(TypeIndex arg_type, void* location)
{
    auto& marshaller = get_marshaller(arg_type);
    return std::make_pair(marshaller.read(location), marshaller.size() + (char*)location);
}


