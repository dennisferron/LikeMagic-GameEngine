


#ifdef _WIN32
#include "Common.h"

BASEKIT_API    int truncate(const char *path, long length);

#else

	#include <unistd.h>

#endif


