
namespace Iocaste {
    namespace Debugger {

template <typename T>
class AbstractOutput
{
public:
    virtual void WriteData(T const& data) = 0;
};

    }
}
