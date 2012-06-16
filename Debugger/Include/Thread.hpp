#pragma once

#include "pthread.h"


namespace Iocaste
{
	namespace Debugger
	{


class Thread
{
public:
	static void usleep(int usec);
	static void nice(int usec);
};


	} // Debugger
} // Iocaste
