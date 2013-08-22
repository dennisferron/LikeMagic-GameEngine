
#include "Interpreter/Bindings.hpp"
#include "Iocaste/Run.hpp"
#include "LikeMagic/StdBindings/TypeSystemInstance.hpp"

int main(int argc, const char *argv[])
{
    LM::type_system = LM::create_typesystem();
    return Iocaste::run(argc, argv, &Interpreter::add_bindings);
}
