
#include "IoFile.h"
#include "IoObject.h"
#include "IoObjectImpl.h"
#include "Iocaste/Exception.hpp"
#include "boost/exception/info.hpp"
#include "boost/exception/get_error_info.hpp"

#include <iostream>

using namespace Iocaste;


extern "C" IO_METHOD(IoObject, doFile)
{
	/*doc Object doFile(pathString)
	Evaluates the File in the context of the receiver. Returns the result.
	pathString is relative to the current working directory.
	*/

    std::string pathString = "<<Error getting file path>>";

    try
    {
        IoSymbol *path = IoMessage_locals_symbolArgAt_(m, locals, 0);

        pathString = CSTRING(path);

        IoFile *file = IoFile_newWithPath_(IOSTATE, path);
        IoSymbol *string = (IoSymbol *)IoSeq_rawAsSymbol(IoFile_contents(file, locals, m));

        if (IoSeq_rawSize(string))
        {
            return IoObject_rawDoString_label_(self, string, path);
        }
        else
        {
            return IONIL(self);
        }
    }
    catch (boost::exception& bex)
    {
        std::vector<std::string> file_stack;

        if( auto err=boost::get_error_info<Iocaste::Exception::file_name_info>(bex) )
            file_stack.insert(file_stack.begin(), err->begin(), err->end());

        file_stack.push_back(pathString);

        bex << Exception::file_name_info(file_stack);

        throw;
    }
}
