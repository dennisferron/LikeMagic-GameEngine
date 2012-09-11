#include "Iocaste/Breakpoint.hpp"
#include "IoMessage.h"
#include "IoSeq.h"

using namespace Iocaste;
using namespace std;

Breakpoint::Breakpoint(
    int breakpoint_number_,
    std::string file_name_,
    int line_number_,
    int char_number_
)
    :
        breakpoint_number(breakpoint_number_),
        file_name(file_name_),
        line_number(line_number_),
        char_number(char_number_)
{
}

// TODO:  Receive args separately?
bool Breakpoint::match(IoMessage* m)
{
    IoMessageData* data = reinterpret_cast<IoMessageData*>(IoObject_dataPointer(m));
    return
        string(CSTRING(data->label)) == file_name &&
        data->lineNumber == line_number &&
        (data->charNumber == char_number || char_number == -1);
}
