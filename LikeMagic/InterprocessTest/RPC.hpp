#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

struct ProcessControlStructure;

struct CallRequest
{
    boost::interprocess::offset_ptr<ProcessControlStructure> sender;
    int call_id;
    int object_handle;
    int method_id;
    int args[20];
};

struct CallReturn
{
    int call_id;
    int rvalue;
};

struct ProcessControlStructure
{
    boost::interprocess::interprocess_semaphore listener;
    boost::interprocess::interprocess_semaphore args_ready;
    boost::interprocess::interprocess_semaphore rvalue_ready;
    bool is_args_ready;
    bool is_rvalue_ready;
    CallRequest args_buffer;
    CallReturn rvalue_buffer;

    ProcessControlStructure()
        : listener(0), args_ready(1), rvalue_ready(1)
            {}
};

struct SharedMemoryFormat
{

    SharedMemoryFormat()
        {}

    // TODO:  Use a boost::interprocess allocator instead
    ProcessControlStructure processes[10];
};

class RPC
{
private:
    char const* shared_memory_name;
    boost::interprocess::shared_memory_object* shm;
    boost::interprocess::mapped_region* region;
    SharedMemoryFormat* data;
    bool is_first;

public:
    RPC(bool is_first_);
    ~RPC();
    void listen(int org_stack_ptr, char const* purpose, int hintmethod);
    int call(int method, int arg);
};
