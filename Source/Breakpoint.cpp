#include "Iocaste/Breakpoint.hpp"
#include "IoMessage.h"
#include "IoSeq.h"
#include <iostream>

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

bool Breakpoint::match(IoMessage* m)
{
    IoMessageData* data = reinterpret_cast<IoMessageData*>(IoObject_dataPointer(m));

    return match(
        string(CSTRING(data->label)),
        data->lineNumber,
        data->charNumber
    );
}

bool Breakpoint::match(std::string file_name_, int line_number_, int char_number_)
{
    cout << "Breakpoint::match(\"" << file_name_ << "\", " << line_number_ << ", " << char_number_ << ")" << endl;
    cout << "Breakpoint fields: \"" << file_name << "\", " << line_number << ", " << char_number << endl;

    bool result =
        file_name_ == file_name &&
        line_number_ == line_number &&
        (char_number_ == char_number || char_number == -1);

    if (result)
    {
        cout << "Breakpoint did match \"" << file_name_ << "\", " << line_number_ << ", " << char_number_ << "" << endl;
    }

    return result;
}
