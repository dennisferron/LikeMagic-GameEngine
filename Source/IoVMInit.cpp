
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>
using namespace std;

#include "IoState.h"
#include "IoObject.h"
#include "IoFile.h"

void doInitFile(IoState* state, IoObject* context, char const* file_path, char const* file_name)
{
    std::ifstream input_stream(file_path);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    string file_content = buffer.str();

    //cout << "Loaded file: " << file_name << endl << file_content << endl;
    IoState_rawOn_doCString_withLabel_(state, context, file_content.c_str(), file_name);
}

extern "C" void IoVMCodeInit(IoObject *context)
{
	IoState *self = IoObject_state((IoObject *)context);

	fprintf(stderr, "Loading startup scripts\n");

	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/A0_List.io", "A0_List.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/A1_OperatorTable.io", "A1_OperatorTable.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/A2_Object.io", "A2_Object.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/A3_List.io", "A3_List.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/A4_Exception.io", "A4_Exception.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Actor.io", "Actor.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/AddonLoader.io", "AddonLoader.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/B_Sequence.io", "B_Sequence.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Block.io", "Block.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/CFunction.io", "CFunction.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Date.io", "Date.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Debugger.io", "Debugger.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Directory.io", "Directory.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/DynLib.io", "DynLib.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Error.io", "Error.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/File.io", "File.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/List_schwartzian.io", "List_schwartzian.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Map.io", "Map.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Number.io", "Number.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Profiler.io", "Profiler.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Sandbox.io", "Sandbox.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Serialize.io", "Serialize.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/System.io", "System.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/UnitTest.io", "UnitTest.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Vector.io", "Vector.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Y_Path.io", "Y_Path.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Z_CLI.io", "Z_CLI.io");
	doInitFile(self, context, "/Users/dennisferron/code/LikeMagic-All/Iocaste/iovm/io/Z_Importer.io", "Z_Importer.io");
}


