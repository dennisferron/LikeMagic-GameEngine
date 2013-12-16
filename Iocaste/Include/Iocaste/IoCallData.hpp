
#pragma once

#include <vector>

struct CollectorMarker;
typedef CollectorMarker IoObject;

namespace Iocaste {

struct IoCallData
{
	IoObject *sender;
	IoObject *message;
	IoObject *target;
	IoObject *slotContext;
	IoObject *activated;
	IoObject *coroutine;
    std::vector<IoObject*> stack_retained;
    int stopStatus;
};

}
