#include "RecombinePrompt.hpp"

using namespace std;
using namespace IoDbg;

RecombinePrompt::RecombinePrompt(
     AbstractOutput<string>& output_)
        : output(output_)
{
}

void RecombinePrompt::WriteData(StringWithPrompt const& data)
{
    output.WriteData( data.content + data.prompt );
}

