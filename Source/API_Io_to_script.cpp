// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/ToIoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/IoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

using namespace LikeMagic;
using namespace LikeMagic::Utility;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::SFMO;

namespace LikeMagic { namespace Backends { namespace Io {

// Note:  This is not Io strings-as-sequences, but actually stuff like vector which is implemented as a sequence.
template <typename T>
IoObject* to_seq(std::vector<T> const& vect, IoState* self)
{
    static TypeInfoPtr to_type = BetterTypeInfo::create<T>();

    // Yuck!  C-style memory alloc!  NAasty...  At least Io frees it for us (I *think*...)
    T* c_buf = reinterpret_cast<T*>(io_calloc(vect.size(), sizeof(T)));

    // TODO:  change CTYPE depending on T.
    UArray* uarray;

    if (*to_type == *BetterTypeInfo::create<int>())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_int32_t, CENCODING_NUMBER, vect.size(), 0);
    else if (*to_type == *BetterTypeInfo::create<unsigned int>())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_uint32_t, CENCODING_NUMBER, vect.size(), 0);
    else
        throw std::logic_error(std::string("No code implemented yet in LikeMagic for converting to IoSeq from ") + to_type->describe());

    // In this case all iterators are pointers, so the STL algorithm here actually uses memcpy for efficiency.
    copy(vect.begin(), vect.end(), c_buf);

    // If you created the Sequence first, it would have just made one uarray and then dropped it when
    // you changed things.  So it's better to create the UArray first and then make it into a sequence.
    return IoSeq_newWithUArray_copy_(self, uarray, 0);
}


#define DECL_CONV(name, type, code) \
struct To##name : public AbstractTypeConverter \
{ \
    static IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m, type value) \
    { \
        return code; \
    } \
    \
    virtual ExprPtr wrap_expr(ExprPtr expr) const \
    { \
        return ToIoObjectExpr<type, To##name>::create(expr); \
    } \
\
    virtual std::string describe() const { return "To " #name " Conv"; } \
}; \

#define ADD_CONV(name, type) \
type_sys.add_converter_simple(BetterTypeInfo::create<type>(), ToIoTypeInfo::create(), new To##name);

DECL_CONV(Number, double, IONUMBER(value))
DECL_CONV(Bool, bool, value? IOTRUE(self) : IOFALSE(self))
DECL_CONV(String, std::string, IOSEQ(reinterpret_cast<const unsigned char*>(value.c_str()), value.length()))

DECL_CONV(Vector_of_Int, std::vector<int> const&, to_seq<int>(value, IOSTATE))
DECL_CONV(Vector_of_UInt, std::vector<unsigned int> const&, to_seq<unsigned int>(value, IOSTATE))

void add_convs_to_script(AbstractTypeSystem& type_sys, IoVM* iovm)
{
    ADD_CONV(Number, double)
    ADD_CONV(Bool, bool)
    ADD_CONV(String, std::string)

    ADD_CONV(Vector_of_Int, std::vector<int> const&)
    ADD_CONV(Vector_of_UInt, std::vector<unsigned int> const&)
}

}}}
