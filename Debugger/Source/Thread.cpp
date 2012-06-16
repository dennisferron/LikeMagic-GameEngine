//#include "stdafx.h"

#include "Thread.hpp"

#ifdef WIN32

// Windows has no usleep() function.  We can use Sleep() instead,
// but we have to include some other headers to get it.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winbase.h>

#else

#include <unistd.h>

#endif


namespace Iocaste
{
	namespace Debugger
	{


void Thread::nice(int usec)
{
	int times = usec / 1000;
	int remainder = usec % 1000;

	for (int i=0; i < times; i++)
	{
#ifdef _LINUX
		pthread_yield();
#endif
		Thread::usleep(1000);
	}

#ifdef _LINUX
	// Yield if we haven't already
	if (times < 1)
		pthread_yield();
#endif

	Thread::usleep(remainder);
}

void Thread::usleep(int usec)
{
#ifdef WIN32
	// Stupid Windows has no usleep() function!
	Sleep(usec/1000);
#else
	// But on Linux we're ok.
	::usleep(usec);
#endif
}


	} // Debugger
} // Iocaste
