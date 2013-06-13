#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/unordered_map.hpp>

using namespace boost::interprocess;

struct ProcessControlStructure;

struct CallRequest
{
    offset_ptr<ProcessControlStructure> sender;
    int invocation_id;
    int object_handle;
    int method_id;
    int args_count;
    char args_buffer[1024];
};

struct CallReturn
{
    int invocation_id;
    char rvalue_buffer[512];
};

template <typename T>
struct DataRegister
{
    interprocess_semaphore available_for_write;
    interprocess_semaphore writing_in_progress;
    bool has_data;
    T data;
    DataRegister() :
        available_for_write(1),
        writing_in_progress(1),
        has_data(false) {}
};

enum class ProcessState
{
    NotStarted = 0,
    WaitForReturn,
    WaitForCommand,

    WaitingToFillCallRequest,
    LockingToWriteCallRequest,
    LockingToReadCallRequest,

    WaitingToFillCallReturn,
    LockingToWriteCallReturn,
    LockingToReadCallReturn,

    LockAcquired,
    LockReleased,
    WaitFinished,

    ExecutingCallRequest
};

struct ProcessControlStructure
{
    ProcessState state;
    boost::interprocess::interprocess_semaphore action_required;
    DataRegister<CallRequest> call_request;
    DataRegister<CallReturn> call_return;

    ProcessControlStructure()
        : action_required(0)
    {
        state = ProcessState::NotStarted;
    }
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
    boost::unordered_map<int, CallReturn> cached_rvalues;

    int invocation_counter;
    ProcessControlStructure* pcs;
    ProcessControlStructure* other_pcs;

    int execute(int method, int arg);
    std::string get_state_name(ProcessState s) const;

public:
    RPC(bool is_first_);
    ~RPC();
    CallReturn listen(int invocation_id, bool wants_rvalue);
    CallReturn call(int object_handle, int method, int arg);
    int call_int(int method, int arg);
    void scan() const;
};
