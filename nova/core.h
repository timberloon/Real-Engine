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

#define BIT(x) (1<<x)

#define sf(x) x*sizeof(float)
#define si(x) x*sizeof(int)
#define sui(x) x*sizeof(unsigned int)

#define stringify(var) #var