#pragma once

#ifdef _WIN32
    #ifdef NOVALIB_BUILD
        #define NOVA_API __declspec(dllexport)
    #else   
        #define NOVA_API __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #ifdef NOVALIB_BUILD
        #define NOVA_API __attribute__((visibility("default")))
    #else   
        #define NOVA_API
    #endif
#else
    #define NOVA_API
#endif
