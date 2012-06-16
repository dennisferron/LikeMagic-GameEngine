#include "CharInput.hpp"

using namespace std;
using namespace Iocaste::Debugger;

CharInput::CharInput(istream& stream_) :
    stream(stream_)
{
}

bool CharInput::HasData() const
{
    return true;
}

string CharInput::ReadData()
{
    string result;
    while (input.good())
    {
        char c ;
        input.get(c);
        debug_log << c << std::flush;
        output    << c << std::flush;
    }

}

