
#include "boost/exception/exception.hpp"
#include <stdexcept>

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;


namespace Iocaste
{
    class Error : boost::exception, std::exception
    {
    private:
        IoError* ioError;

    public:
        Error(IoError* ioError_);
    };
}
