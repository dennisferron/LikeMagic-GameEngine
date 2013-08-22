#include "LikeMagic/Interprocess/SharedArgTransporter.hpp"

#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"

#include "LikeMagic/Interprocess/SharedMemoryFormat.hpp"

using namespace boost::interprocess;

namespace LM {

typedef int ObjectHandle;
typedef int MethodId;
typedef int InvocationId;

class SharedObjectRegistry;

class RequestBroker
{
private:
    SharedObjectRegistry& object_registry;

    boost::unordered_map<InvocationId, CallReturn> cached_rvalues;

    int invocation_counter;
    ProcessControlStructure* pcs;

    std::string get_state_name(ProcessState s) const;

    SharedArgTransporter transporter;

public:
    RequestBroker(SharedObjectRegistry& object_registry_, ProcessControlStructure* pcs_);
    ~RequestBroker();
    CallReturn listen(InvocationId invocation_id, bool wants_rvalue);
    CallReturn call(ProcessControlStructure* target_pcs, ObjectHandle object_handle,
                               MethodId method_id, TypeInfoList arg_types, ArgList args);
};

}
