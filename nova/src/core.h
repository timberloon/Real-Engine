#pragma once

#ifdef _WIN32
    #ifdef NOVALIB_BUILD
        #define NOVAAPI __declspec(dllexport)
    #else   
        #define NOVAAPI __declspec(dllimport)
    #endif
#else
    #error Nova is for windows only
#endif
