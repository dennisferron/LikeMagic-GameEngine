#include "AbstractAdapter.hpp"
#include "GdbResponse.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseWriter : public AbstractAdapter<GdbResponse>
{
private:
    AbstractOutput<std::string>& sink;
    std::string Write(GdbResponse const& response) const;

public:
    GdbResponseWriter(AbstractOutput<std::string>& sink_);
    virtual void WriteData(GdbResponse const& input);
};

}}
