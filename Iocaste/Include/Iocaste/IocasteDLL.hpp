
#if (defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__)
  #ifdef BUILDING_IOCASTE_DLL
    #ifdef __GNUC__
      #define IOCASTE_API __attribute__((dllexport))
    #else
      #define IOCASTE_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define IOCASTE_API __attribute__((dllimport))
    #else
      #define IOCASTE_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
#else
    #define IOCASTE_API
#endif
