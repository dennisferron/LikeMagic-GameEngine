
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>
using namespace std;

#include "IoState.h"
#include "IoObject.h"
#include "IoFile.h"

void doInitFile(IoState* state, IoObject* context, std::string file_path, char const* file_name)
{
    try
    {
        IoState_doFile_(state, file_path.c_str());
    }
    catch (...)
    {
        cerr << "Exception opening/reading Io initialization file " << file_path << endl;
        throw;
    }
}

extern "C" void IoVMCodeInit(IoObject *context, char const* bootstrap_path)
{
	IoState *self = IoObject_state((IoObject *)context);

	fprintf(stderr, "Loading startup scripts\n");

	std::string bootstrap_path_as_string(bootstrap_path);

	doInitFile(self, context, bootstrap_path_as_string + "A0_List.io", "A0_List.io");
	doInitFile(self, context, bootstrap_path_as_string + "A1_OperatorTable.io", "A1_OperatorTable.io");
	doInitFile(self, context, bootstrap_path_as_string + "A2_Object.io", "A2_Object.io");
	doInitFile(self, context, bootstrap_path_as_string + "A3_List.io", "A3_List.io");
	doInitFile(self, context, bootstrap_path_as_string + "A4_Exception.io", "A4_Exception.io");
	doInitFile(self, context, bootstrap_path_as_string + "Actor.io", "Actor.io");
	doInitFile(self, context, bootstrap_path_as_string + "AddonLoader.io", "AddonLoader.io");
	doInitFile(self, context, bootstrap_path_as_string + "B_Sequence.io.inl", "B_Sequence.io.inl");
	doInitFile(self, context, bootstrap_path_as_string + "Block.io", "Block.io");
	doInitFile(self, context, bootstrap_path_as_string + "CFunction.io", "CFunction.io");
	doInitFile(self, context, bootstrap_path_as_string + "Date.io", "Date.io");
	doInitFile(self, context, bootstrap_path_as_string + "Debugger.io", "Debugger.io");
	doInitFile(self, context, bootstrap_path_as_string + "Directory.io", "Directory.io");
	doInitFile(self, context, bootstrap_path_as_string + "DynLib.io", "DynLib.io");
	doInitFile(self, context, bootstrap_path_as_string + "Error.io", "Error.io");
	doInitFile(self, context, bootstrap_path_as_string + "File.io", "File.io");
	doInitFile(self, context, bootstrap_path_as_string + "List_schwartzian.io", "List_schwartzian.io");
	doInitFile(self, context, bootstrap_path_as_string + "Map.io", "Map.io");
	doInitFile(self, context, bootstrap_path_as_string + "Number.io", "Number.io");
	doInitFile(self, context, bootstrap_path_as_string + "Profiler.io", "Profiler.io");
	doInitFile(self, context, bootstrap_path_as_string + "Sandbox.io", "Sandbox.io");
	doInitFile(self, context, bootstrap_path_as_string + "Serialize.io", "Serialize.io");
	doInitFile(self, context, bootstrap_path_as_string + "System.io", "System.io");
	doInitFile(self, context, bootstrap_path_as_string + "UnitTest.io", "UnitTest.io");
	doInitFile(self, context, bootstrap_path_as_string + "Vector.io", "Vector.io");
	doInitFile(self, context, bootstrap_path_as_string + "Y_Path.io", "Y_Path.io");
	doInitFile(self, context, bootstrap_path_as_string + "Z_CLI.io", "Z_CLI.io");
	doInitFile(self, context, bootstrap_path_as_string + "Z_Importer.io", "Z_Importer.io");
}


