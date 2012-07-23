#include "CharInput.hpp"
#include <boost/algorithm/string/predicate.hpp>


using namespace std;
using namespace Iocaste::Debugger;

CharInput::CharInput(istream& stream_) :
    stream(stream_)
{
}

bool CharInput::HasData() const
{
    return stream.good();
}

string CharInput::ReadData()
{
    char c;
    stream.get(c);
    return string(1, c);
}

