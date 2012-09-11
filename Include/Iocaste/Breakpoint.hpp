
#include <string>

extern "C" {

// Using forward declarations here so that user of IoVM class doesn't
// actually need to include Io headers to create an IoVM object.
struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;

}

namespace Iocaste {

class Breakpoint
{
private:

    int breakpoint_number;
    std::string file_name;
    int line_number;
    int char_number;

public:

    Breakpoint(
        int breakpoint_number_,
        std::string file_name_,
        int line_number_,
        int char_number_
    );

    bool match(IoMessage* m);
};

}
