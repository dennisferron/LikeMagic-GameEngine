#ifndef IOVM_API_H_
#define IOVM_API_H_

#if defined(NO_USE_DLL_BUILD)
#define IOVM_API
#else

#if defined(WIN32)
#if defined(BUILDING_IOVM_DLL) || defined(BUILDING_IOVMALL_DLL)
#define IOVM_API __declspec(dllexport)
#else
#define IOVM_API __declspec(dllimport)
#endif

#else
#define IOVM_API
#endif

#endif

#endif
