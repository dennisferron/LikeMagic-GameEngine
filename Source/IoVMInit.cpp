
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>
using namespace std;

#include "IoState.h"
#include "IoObject.h"
#include "IoFile.h"

#define BOOTSTRAP_FILE_PATH "../Iocaste/iovm/io/"

void doInitFile(IoState* state, IoObject* context, char const* file_path, char const* file_name)
{
    std::ifstream input_stream(file_path);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    string file_content = buffer.str();

    //cout << "Loaded file: " << file_name << endl << file_content << endl;
    IoState_rawOn_doCString_withLabel_(state, context, file_content.c_str(), file_path);
}

extern "C" void IoVMCodeInit(IoObject *context)
{
	IoState *self = IoObject_state((IoObject *)context);

	fprintf(stderr, "Loading startup scripts\n");

	doInitFile(self, context, BOOTSTRAP_FILE_PATH "A0_List.io", "A0_List.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "A1_OperatorTable.io", "A1_OperatorTable.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "A2_Object.io", "A2_Object.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "A3_List.io", "A3_List.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "A4_Exception.io", "A4_Exception.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Actor.io", "Actor.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "AddonLoader.io", "AddonLoader.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "B_Sequence.io.inl", "B_Sequence.io.inl");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Block.io", "Block.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "CFunction.io", "CFunction.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Date.io", "Date.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Debugger.io", "Debugger.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Directory.io", "Directory.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "DynLib.io", "DynLib.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Error.io", "Error.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "File.io", "File.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "List_schwartzian.io", "List_schwartzian.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Map.io", "Map.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Number.io", "Number.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Profiler.io", "Profiler.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Sandbox.io", "Sandbox.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Serialize.io", "Serialize.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "System.io", "System.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "UnitTest.io", "UnitTest.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Vector.io", "Vector.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Y_Path.io", "Y_Path.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Z_CLI.io", "Z_CLI.io");
	doInitFile(self, context, BOOTSTRAP_FILE_PATH "Z_Importer.io", "Z_Importer.io");
}


