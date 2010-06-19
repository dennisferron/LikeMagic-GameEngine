#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/IoObjectExpr.hpp"

#include "LikeMagic/Backends/Io/IoListSTL.hpp"
#include "LikeMagic/Backends/Io/IoVectorSTL.hpp"

#include <vector>
#include <algorithm>

namespace LikeMagic { namespace Backends { namespace Io {

template <typename T>
ExprPtr from_vector(IoObject* io_obj)
{
    IoVectorSTL<T> io_vector(io_obj);

    std::vector<T> cpp_vector(io_vector.size());

    copy(io_vector.begin(), io_vector.end(), cpp_vector.begin());

    return Term<std::vector<T>, true>::create(cpp_vector);
}

template <typename T>
ExprPtr from_list(IoObject* io_obj)
{
    IoListSTL<T> io_list(io_obj);

    std::vector<T> cpp_vector(io_list.size());

    copy(io_list.begin(), io_list.end(), cpp_vector.begin());

    return Term<std::vector<T>, true>::create(cpp_vector);
}


ExprPtr from_script(IoObject* self, IoObject* io_obj, BetterTypeInfo expected_type, AbstractTypeSystem const& type_sys)
{
    // TODO:  These can all be made into converters that convert IoObjectExpr into the needed expression type.
    // These converters could be plugged into the type graph, and then from_script need only do: return IoObjectExpr::create(io_obj);

    if (ISNUMBER(io_obj))
        return Term<double, true>::create(IoNumber_asDouble(io_obj));
    else if (ISVECTOR(io_obj))
    {
        if (expected_type.bare_type().is_type<std::vector<double>>())
            return from_vector<double>(io_obj);
        else if (expected_type.bare_type().is_type<std::vector<long>>())
            return from_vector<long>(io_obj);
        else if (expected_type.bare_type().is_type<std::vector<short>>())
            return from_vector<short>(io_obj);
        else if (expected_type.bare_type().is_type<std::vector<unsigned long>>())
            return from_vector<unsigned long>(io_obj);
        else if (expected_type.bare_type().is_type<std::vector<unsigned short>>())
            return from_vector<unsigned short>(io_obj);
        else if (expected_type.bare_type().is_type<unsigned short>() && expected_type.is_ptr)
            return from_vector<unsigned short>(io_obj);
        else
            //throw std::invalid_argument(std::string("Cannot convert Io Vector to STL vector of type ")
            //    + expected_type.bare_type().describe());
            return IoObjectExpr::create(io_obj);
    }
    else if (ISLIST(io_obj))
    {
        if (expected_type.is_type<std::vector<double>>())
            return from_list<double>(io_obj);
//        else if (expected_type.is_type<std::vector<long>>())
//            return from_list<long>(io_obj);
//        else if (expected_type.is_type<std::vector<short>>())
//            return from_list<short>(io_obj);
//        else if (expected_type.is_type<std::vector<unsigned long>>())
//            return from_list<unsigned long>(io_obj);
//        else if (expected_type.is_type<std::vector<unsigned short>>())
//            return from_list<unsigned short>(io_obj);
        else
            //throw std::invalid_argument(std::string("Cannot convert Io List to STL vector of type ")
            //    + expected_type.describe());
            return IoObjectExpr::create(io_obj);
    }
    else if (ISSEQ(io_obj))
        return Term<std::string, true>::create(IoSeq_asCString(io_obj));
    else if (ISNIL(io_obj))
        return NullExpr<IoNilExprTag*>::create();
    else if (ISBOOL(io_obj))
        return Term<bool, true>::create(ISTRUE(io_obj));
    else if (ISBLOCK(io_obj))
        return Term<IoBlock, true>::create(&type_sys, io_obj, self);
    else if (is_sfmo_obj(io_obj))
    {
        AbstractCppObjProxy* proxy(
                reinterpret_cast<AbstractCppObjProxy*>
                    (IoObject_dataPointer(io_obj)));
        proxy->check_magic();
        return proxy->get_expr();
    }
    else
    {
        //throw std::invalid_argument(std::string("CallContext_io::from_script:  I don't know what to do with an Io object with tag of ")
        //        + IoObject_tag(io_obj)->name);
        return IoObjectExpr::create(io_obj);
    }
}

}}}
