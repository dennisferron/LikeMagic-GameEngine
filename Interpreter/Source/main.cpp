
#include "Interpreter/Bindings.hpp"
#include "Iocaste/Run.hpp"

int main(int argc, const char *argv[])
{
    return Iocaste_run(argc, argv, &Interpreter::add_bindings);
}
