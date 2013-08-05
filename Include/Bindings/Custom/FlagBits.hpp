// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

// forward declaration
namespace irr { namespace scene {
    class ISceneNode;
}}

namespace Bindings { namespace Custom {

int  flag_bits_get_value(irr::scene::ISceneNode* node);
void flag_bits_set_value(irr::scene::ISceneNode* node, int value);

// Because Io uses double internally for Number, it has trouble
// with bit-twiddling operations on nominal integers.  Not all the bits
// get preserved during certain operations.  This is a utility class
// to provide reliable primitives for bit-flag operations.
// However, since LikeMagic auto-converts integers to Io Numbers if it can,
// we can't simply pass and return ints from this class because allowing
// the integers to round-trip through Io Numbers (doubles) negates the
// whole purpose!  So instead of passing and returning integers,
// this class instead holds the containing object and calls functions
// flag_bits_get_value and flag_bits_set_value *on the parent object*.
// I used a trick I learned from the implementation of boost intrusive_ptr,
// which is to have the user overload a free function to customize
// the behavior for the type of object.  You should overload flag_bits_get_value
// and flag_bits_set_value for the type of object you pass for T to FlagBits<T>.

// Given the above explanation that we mustn't pass the bare
// integer flags value through Io, you might wonder don't the methods
// extractNumber and embedNumber contradict that?
// The methods extractNumber and embedNumber are safe if and only if
// you do not exceed some max number of significant bits.  I do not
// know for certain how many bits this is.  I would have expected
// a double to be able to represent integers up to 48 bits, but
// have observed Io numbers choke on less than 32 significant bits,
// so I don't know what to think about that.

// I intend to make Iocaste support integers natively for this reason.

template <typename T>
class FlagBits
{
private:

    T object;

    int bit_pos(int index)
    {
        // Return type of user-defined overload determines what type the flags are stored in.
        typedef decltype(flag_bits_get_value(object)) value_type;

        if (index >= 0)                             // If positive index
            return index;                           // then index from LSB
        else                                        // Else negative index
            return sizeof(value_type)/8 + index;    // then index from MSB
    }

public:

    explicit FlagBits(T object_) : object(object_) {}

    bool getBit(int index)
    {
        // Use user-defined overload to retrieve value.
        auto value = flag_bits_get_value(object);
        return 1 & (value >> bit_pos(index));
    }

    void setBit(int index, bool state)
    {
        // Use user-defined overload to retrieve value.
        auto value = flag_bits_get_value(object);

        if (state)
            value |=  (1 << bit_pos(index));
        else
            value &= ~(1 << bit_pos(index));

        // Use user-defined overload to store value.
        flag_bits_set_value(object, value);
    }

    // Can be used to get an embedded number or get a block of flag bits at once.
    unsigned int extractNumber(int msbIndex, int lsbIndex)
    {
        // Use user-defined overload to retrieve value.
        auto value = flag_bits_get_value(object);

        // If the msb or lsb are indexed from the msb, convert to pos.
        int msbPos = bit_pos(msbIndex);
        int lsbPos = bit_pos(lsbIndex);

        unsigned int result = 0;
        for (int pos=msbPos; pos>=lsbPos; --pos, result<<=1)
            result |= 1 & (value >> pos);

        return result;
    }

    // Can be used to store a number in a range of bits or to set a block of flag bits at once.
    void embedNumber(int msbIndex, int lsbIndex, unsigned int number)
    {
        // Use user-defined overload to retrieve value.
        auto value = flag_bits_get_value(object);

        // If the msb or lsb are indexed from the msb, convert to pos.
        int msbPos = bit_pos(msbIndex);
        int lsbPos = bit_pos(lsbIndex);

        unsigned int bit_stream = number;
        for (int pos=lsbPos; pos<=msbPos; ++pos, bit_stream >>= 1)
        {
            if (bit_stream & 1)
                value |=   1 << pos;
            else
                value &= ~(1 << pos);
        }

        // Use user-defined overload to store value.
        flag_bits_set_value(object, value);
    }
};

}}
