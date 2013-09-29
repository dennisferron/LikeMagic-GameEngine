
#if defined(USE_DLL_BUILD) && (defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__)
  #ifdef BUILDING_LIKEMAGIC_DLL
    #ifdef __GNUC__
      #define LIKEMAGIC_API __attribute__((dllexport))
    #else
      #define LIKEMAGIC_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define LIKEMAGIC_API __attribute__((dllimport))
    #else
      #define LIKEMAGIC_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
#else
    #define LIKEMAGIC_API
#endif
