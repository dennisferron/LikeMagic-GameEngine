#include <cxxabi.h>

#include <string>
#include <malloc.h>

namespace LikeMagic { namespace Utility {

std::string demangle_name(std::string type_name)
{
    int status;
    char* buf = abi::__cxa_demangle(type_name.c_str(), 0, 0, &status);
    std::string result(buf);
    free(buf);
    return result;
}

}}
