#ifdef COMPILE_DLL
    #define dllapi _declspec(dllexport)
#else
    #define dllapi 
    // _declspec(dllimport)
#endif