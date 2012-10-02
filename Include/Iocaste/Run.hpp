
namespace LikeMagic
{
    class RuntimeTypeSystem;
}

namespace Iocaste
{
    int run(int argc, const char *argv[], void (*add_bindings)(LikeMagic::RuntimeTypeSystem&), LikeMagic::RuntimeTypeSystem* type_sys);
}

