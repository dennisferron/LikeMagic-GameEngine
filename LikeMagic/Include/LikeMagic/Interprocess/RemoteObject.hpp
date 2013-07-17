#pragma once

namespace LikeMagic { namespace Interprocess

typedef int ProcessHandle;
typedef int ObjectHandle;

class RemoteObject
{
private:
    ProcessHandle remote_process;
    ObjectHandle remote_object;

public:
};

}}
