#include "AbstractAdapter.hpp"
#include "AbstractInput.hpp"
#include "GdbResponse.hpp"
#include "StringWithPrompt.hpp"
#include "UserCmd.hpp"

namespace IoDbg {

class GdbResponseWriter : public AbstractAdapter<GdbResponse>
{
private:
    AbstractOutput<StringWithPrompt>& sink;
    AbstractInput<UserCmd>& fromUser;
    std::string Write(std::vector<GdbResponseType> const& response) const;
    std::string last_prompt;

public:
    GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_, AbstractInput<UserCmd>& fromUser_);
    virtual void WriteData(GdbResponse const& input);
};

}
