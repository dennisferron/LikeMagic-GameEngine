#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"

namespace LikeMagic { namespace Backends { namespace Io {

template <typename T>
IoObject* to_seq(LikeMagic::SFMO::AbstractCppObjProxy* proxy, IoState* self)
{
    BetterTypeInfo to_type = BetterTypeInfo::create<T>();

    auto expr = proxy->try_conv<std::vector<T>&>();
    auto vect = expr->eval();

    // Yuck!  C-style memory alloc!  NAasty...  At least Io frees it for us (I *think*...)
    T* c_buf = reinterpret_cast<T*>(io_calloc(vect.size(), sizeof(T)));

    // TODO:  change CTYPE depending on T.
    UArray* uarray;

    if (to_type == BetterTypeInfo::create<int>())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_int32_t, CENCODING_NUMBER, vect.size(), 0);
    else if (to_type == BetterTypeInfo::create<unsigned int>())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_uint32_t, CENCODING_NUMBER, vect.size(), 0);
    else
        throw std::logic_error(std::string("No code implemented yet in LikeMagic for converting to IoSeq from ") + to_type.describe());

    // In this case all iterators are pointers, so the STL algorithm here actually uses memcpy for efficiency.
    copy(vect.begin(), vect.end(), c_buf);

    // If you created the Sequence first, it would have just made one uarray and then dropped it when
    // you changed things.  So it's better to create the UArray first and then make it into a sequence.
    return IoSeq_newWithUArray_copy_(self, uarray, 0);
}


IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy)
{
    IoState* state = IOSTATE;

    if (!proxy)
    {
        //cout << "to_script(): no proxy, returning nil." << endl;
        return state->ioNil;
    }
    else
    {
        proxy->check_magic();
    }

    IoObject* result;

    if (proxy->is_terminal())
    {
        if (proxy->is_bool())
        {
            result = proxy->to_bool()? IOTRUE(self) : IOFALSE(self);
            delete proxy;
            return result;
        }
        else if (proxy->is_number())
        {
            double d = proxy->to_number();
            if (d!=d)
                std::cout << "NaN!" << std::endl;

            result = IONUMBER(proxy->to_number());
            delete proxy;
            return result;
        }
        else if (proxy->is_string())
        {
            std::string str = proxy->to_string();
            result = IOSEQ(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
            delete proxy;
            return result;
        }
        else if (proxy->is_vector_of(typeid(int)))
        {
            result = to_seq<int>(proxy, state);
            delete proxy;
            return result;
        }
        else if (proxy->is_vector_of(typeid(unsigned int)))
        {
            result = to_seq<unsigned int>(proxy, state);
            delete proxy;
            return result;
        }
    }

    // else proxy is not terminal or does not have implicit conversion to Io type.

    string io_code = "LikeMagic classes " + proxy->get_class_name() + " clone";
    result = IoState_doCString_(state, io_code.c_str());
    IoObject_setDataPointer_(result, proxy);

    return result;
}

}}}