
#include "Interpreter/Bindings.hpp"
#include "Iocaste/Run.hpp"

int main(int argc, const char *argv[])
{
    return Iocaste::run(argc, argv, &Interpreter::add_bindings);
}
