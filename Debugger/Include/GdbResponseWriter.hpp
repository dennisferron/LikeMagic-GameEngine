#include "AbstractAdapter.hpp"
#include "GdbResponse.hpp"
#include "StringWithPrompt.hpp"

namespace Iocaste { namespace Debugger {

class GdbResponseWriter : public AbstractAdapter<GdbResponse>
{
private:
    AbstractOutput<StringWithPrompt>& sink;
    std::string Write(std::vector<GdbResponseType> const& response) const;
    std::string last_prompt;

public:
    GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_);
    virtual void WriteData(GdbResponse const& input);
};

}}
