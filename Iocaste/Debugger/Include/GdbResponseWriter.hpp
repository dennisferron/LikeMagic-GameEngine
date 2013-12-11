#include "AbstractAdapter.hpp"
#include "AbstractInput.hpp"
#include "GdbResponse.hpp"
#include "StringWithPrompt.hpp"
#include "UserCmd.hpp"

namespace IoDbg {

class GdbResponseWriter : public AbstractAdapter<Rules::GdbResponse>
{
private:
    AbstractOutput<StringWithPrompt>& sink;
    AbstractInput<Rules::UserCmd>& fromUser;
    std::string Write(std::vector<Rules::GdbResponseType> const& response) const;
    std::string last_prompt;

public:
    GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_, AbstractInput<Rules::UserCmd>& fromUser_);
    virtual void WriteData(Rules::GdbResponse const& input);
};

}
