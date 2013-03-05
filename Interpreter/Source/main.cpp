
#include "Interpreter/Bindings.hpp"
#include "Iocaste/Run.hpp"
#include "LikeMagic/StdBindings/TypeSystemInstance.hpp"

int main(int argc, const char *argv[])
{
    return Iocaste::run(argc, argv, &Interpreter::add_bindings, LikeMagic::StdBindings::create_typesystem());
}
