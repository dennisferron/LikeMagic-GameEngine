
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <sstream>
using namespace std;

#include "IoState.h"
#include "IoObject.h"
#include "IoFile.h"

void doInitFile(IoState* state, IoObject* context, std::string file_path)
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

	char buf[1024];
	char* cwd = (char *)getcwd(buf, 1024);

	cout << "Loading startup scripts, cwd is " << cwd << " and bootstrap path is " << bootstrap_path << endl;

	std::string bootstrap_path_as_string(bootstrap_path);

	doInitFile(self, context, bootstrap_path_as_string + "A0_List.io");
	doInitFile(self, context, bootstrap_path_as_string + "A1_OperatorTable.io");
	doInitFile(self, context, bootstrap_path_as_string + "A2_Object.io");
	doInitFile(self, context, bootstrap_path_as_string + "A3_List.io");
	doInitFile(self, context, bootstrap_path_as_string + "A4_Exception.io");
	doInitFile(self, context, bootstrap_path_as_string + "Actor.io");
	doInitFile(self, context, bootstrap_path_as_string + "AddonLoader.io");
	doInitFile(self, context, bootstrap_path_as_string + "B_Sequence.io.inl");
	doInitFile(self, context, bootstrap_path_as_string + "Block.io");
	doInitFile(self, context, bootstrap_path_as_string + "CFunction.io");
	doInitFile(self, context, bootstrap_path_as_string + "Date.io");
	doInitFile(self, context, bootstrap_path_as_string + "Debugger.io");
	doInitFile(self, context, bootstrap_path_as_string + "Directory.io");
	doInitFile(self, context, bootstrap_path_as_string + "DynLib.io");
	doInitFile(self, context, bootstrap_path_as_string + "Error.io");
	doInitFile(self, context, bootstrap_path_as_string + "File.io");
	doInitFile(self, context, bootstrap_path_as_string + "List_schwartzian.io");
	doInitFile(self, context, bootstrap_path_as_string + "Map.io");
	doInitFile(self, context, bootstrap_path_as_string + "Number.io");
	doInitFile(self, context, bootstrap_path_as_string + "Profiler.io");
	doInitFile(self, context, bootstrap_path_as_string + "Sandbox.io");
	doInitFile(self, context, bootstrap_path_as_string + "Serialize.io");
	doInitFile(self, context, bootstrap_path_as_string + "System.io");
	doInitFile(self, context, bootstrap_path_as_string + "UnitTest.io");
	doInitFile(self, context, bootstrap_path_as_string + "Vector.io");
	doInitFile(self, context, bootstrap_path_as_string + "Y_Path.io");
	doInitFile(self, context, bootstrap_path_as_string + "Z_CLI.io");
	doInitFile(self, context, bootstrap_path_as_string + "Z_Importer.io");
}
