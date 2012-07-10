#include "AbstractOutput.hpp"


class GdbResponseWriter : public AbstractOutput<GdbResponse>
{
private:
    AbstractOutput<std::string> sink;

public:
    GdbResponseWriter(AbstractOutput<std::string>& sink_);
    virtual void WriteData(GdbResponse input);
};
