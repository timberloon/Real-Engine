#pragma once

#ifdef _WIN32
    #ifdef NOVALIB_BUILD
        #define NOVA_API __declspec(dllexport)
    #else   
        #define NOVA_API __declspec(dllimport)
    #endif
#else
    #define NOVA_API
    #error Nova is for windows only
#endif
